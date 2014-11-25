#include "mp4reader.h"
#include "mp4box.h"

#include <iostream>
#include <stdio.h>
#include <cstring>

using std::cout; using std::endl;

MP4Reader::MP4Reader(char *bytes, unsigned int length, MP4Box *parent)
{
    if(parent) m_topNode = parent;
    else {
        m_topNode = new MP4Box("root");
    }
    m_bytes = bytes;
    m_length = length;
    m_nextBoxAt = 8;
}

MP4FileReader::MP4FileReader(string filename, int totalNumberOfBytes) :
    m_totalNumberOfBytes(totalNumberOfBytes)
{
    m_filename = filename;
}

void MP4Reader::readBoxes() {
    while(m_currentLocation + 4 < m_length) {
        MP4Box::readBox(this, m_topNode);
    }
}

void MP4Reader::readHeader(unsigned int &length, string &type) {
    length = readUInt();
    type = read4Chars();
}

void MP4Reader::skipBytes(int numBytes) {
    cout << "    Skipping " << numBytes << " bytes." << endl;
    m_currentLocation += numBytes;
}

void MP4Reader::readBytes(int numBytes, void *destination)
{
    cout << "    Reading " << numBytes << " bytes - " << remainingBytes() << " bytes left in atom." << endl;
    memcpy(destination, &m_bytes[m_currentLocation], numBytes);
    m_currentLocation += numBytes;
}

string MP4Reader::readISO639()
{
    short bits = readUShort();
    return "";
}

string MP4Reader::readUTF8(int length) {
    // TODO: Use http://utfcpp.sourceforge.net/

    //    char str[length+1];
    //    readBytes(length, str);
    //    str[length] = 0;
    return "";
}

void MP4Reader::readPString() {
    unsigned char len;
    readBytes(1, &len);
    skipBytes(len);
}

std::string MP4Reader::read4Chars()
{
    char str[5];
    str[4] = 0; // terminate character
    readBytes(4*sizeof(char), str);
    return string(str);
}

short MP4Reader::readShort()
{
    short n;
    readBytes(sizeof(short), &n);
    n = __builtin_bswap32(n);

    return n;
}

unsigned short MP4Reader::readUShort()
{
    unsigned short n;
    readBytes(sizeof(unsigned short), &n);
    n = __builtin_bswap32(n);

    return n;
}

char MP4Reader::readChar()
{
    char n;
    readBytes(sizeof(char), &n);
    n = __builtin_bswap32(n);

    return n;
}

unsigned char MP4Reader::readUChar()
{
    unsigned char n;
    readBytes(sizeof(unsigned char), &n);
    n = __builtin_bswap32(n);

    return n;
}

int MP4Reader::readInt()
{
    int n;
    readBytes(sizeof(int), &n);
    n = __builtin_bswap32(n);

    return n;
}

void MP4Reader::readUIntArray(int length, unsigned int *array)
{
    for(int i=0; i<length; i++) {
        readBytes(sizeof(unsigned int), &array[i]);
        array[i] = __builtin_bswap32(array[i]);
    }
}

void MP4Reader::newBoxLength(unsigned int length)
{
    m_nextBoxAt = m_currentLocation + length - 8; // We have already used 8 bytes for the header
    // cout << "New box length: " << length << " giving next box at " << m_nextBoxAt << endl;
}

void MP4Reader::skipRemainingBytes() {
    unsigned int bytesLeftInBox = remainingBytes();
    cout << "Skipping the remaining " << bytesLeftInBox << " bytes in this atom." << endl;
    skipBytes(bytesLeftInBox);
}

unsigned int MP4Reader::remainingBytes()
{
    return m_nextBoxAt - m_currentLocation;
}

MP4Reader *MP4Reader::subReader(MP4Box *parent)
{
    MP4Reader *subReader = new MP4Reader(&m_bytes[m_currentLocation], remainingBytes(), parent);
    return subReader;
}

float MP4Reader::readFP16()
{
    int n = readInt();
    return float(n)/65536.0f;
}

float MP4Reader::readFP8()
{
    short n = readShort();
    return float(n)/256.0f;
}

unsigned int MP4Reader::readUInt()
{
    unsigned int n;
    readBytes(sizeof(unsigned int), &n);
    n = __builtin_bswap32(n);

    return n;
}

bool MP4FileReader::open()
{
    m_file.open(m_filename, std::ios::binary | std::ios::in);
    if(m_file.is_open()) return true;
    else {
        std::cout << "Could not open file " << m_filename << std::endl;
        return false;
    }

    if(m_totalNumberOfBytes == -1) {
        // We have the whole file
        cout << "We are asked to read the whole file" << endl;
        readBytesFromFile(-1);
    }
}

void MP4FileReader::ensureOpen() {
    if(!m_file.is_open()) {
        cout << "File " << m_filename << " is not open, opening..." << endl;
        open();
    }
}

void MP4FileReader::readBytesFromFile(int numBytes) {
    // TODO: Possibly broken and not general at all...
    ensureOpen();
    if(numBytes == -1) {
        m_file.seekg (0, m_file.end);
        numBytes = m_file.tellg();
        m_file.seekg (0, m_file.beg);
        cout << "Will read the whole file which is " << numBytes << " bytes long." << endl;
        m_totalNumberOfBytes = numBytes;
    }
    m_bytes = new char[numBytes];
    m_file.read(reinterpret_cast<char*>(m_bytes), numBytes);
}

void MP4FileReader::read()
{
    readBytesFromFile(-1);
    cout << "Total number of bytes in file: " << m_totalNumberOfBytes << endl;
    MP4Reader *reader = new MP4Reader(m_bytes, m_totalNumberOfBytes, 0);
    reader->readBoxes();
}
