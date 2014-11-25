#include "mp4reader.h"
#include "mp4box.h"

#include <iostream>
#include <stdio.h>
#include <cstring>

using std::cout; using std::endl;

MP4Reader::MP4Reader(string filename, int totalNumberOfBytes) :
    m_currentLocation(0),
    m_totalNumberOfBytes(totalNumberOfBytes),
    m_topNode(0),
    m_nextBoxAt(0)
{
    m_filename = filename;
}

void MP4Reader::readHeader(unsigned int &length, string &type) {
    length = readUInt();
    type = read4Chars();
}

void MP4Reader::readBytes(int numBytes, void *destination)
{
    memcpy(destination, &m_bytes[m_currentLocation], numBytes);
    m_currentLocation += numBytes;
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
    m_nextBoxAt = m_currentLocation + length;
}

void MP4Reader::skipRemainingBytes() {
    unsigned int bytesLeftInBox = m_nextBoxAt - m_currentLocation;
    skipBytes(bytesLeftInBox);
}

unsigned int MP4Reader::readUInt()
{
    unsigned int n;
    readBytes(sizeof(unsigned int), &n);
    n = __builtin_bswap32(n);

    return n;
}

bool MP4Reader::open()
{
    m_file.open(m_filename, std::ios::binary | std::ios::in);
    if(m_file.is_open()) return true;
    else {
        std::cout << "Could not open file " << m_filename << std::endl;
        return false;
    }
}

void MP4Reader::ensureOpen() {
    if(!m_file.is_open()) {
        open();
    }
}

void MP4Reader::readBoxes() {
    readBytesFromFile(m_totalNumberOfBytes);
    m_topNode = MP4Box::readBox(this, 0);

    bool shouldContinueReading = true;
    while(shouldContinueReading) {
        // readBox(m_topNode);
    }
}

void MP4Reader::readBytesFromFile(int numBytes) {
    ensureOpen();
    int currentLocation = m_bytes.size();
    m_bytes.resize(numBytes + m_bytes.size(), 0);

    m_file.read(reinterpret_cast<char*>(&m_bytes[currentLocation]), numBytes);
}
