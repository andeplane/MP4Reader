#include "mp4reader.h"
#include "mp4reader.h"
#include "mp4box.h"
#include "track.h"
#include "mp4file.h"

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cassert>

using std::cout; using std::endl;

MP4Reader::MP4Reader(char *bytes, unsigned int length, unsigned int offset, MP4File *file, unsigned int readerDepth, MP4Box *parent)
{
    if(parent) m_topNode = parent;
    else {
        m_topNode = new MP4Box("root");
    }
    m_offset = offset;
    m_bytes = bytes;
    m_length = length;
    m_file = file;
    m_nextBoxAt = 8;
    m_currentLocation = 0;
    m_readerDepth = readerDepth;
    log(MP4VerboseLevel::High, "Created new MP4Reader with offset "+to_string(offset)+" and length "+to_string(length));
}

void MP4Reader::readBoxes() {
    while(m_currentLocation + 4 < m_length) {
        MP4Box::readBox(this, m_topNode);
    }
    if(m_topNode->name().compare("root") == 0) {
        cout << "Main reader finished." << endl;
    }
}

void MP4Reader::readHeader(unsigned int &length, string &type) {
    length = readUInt();
    type = read4Chars();
    log(MP4VerboseLevel::Full, "Read header with type '"+type+"' and length "+to_string(length));
}

void MP4Reader::skipBytes(int numBytes) {
    log(MP4VerboseLevel::Full, "Skipping "+to_string(numBytes)+" bytes.");
    m_currentLocation += numBytes;
}

void MP4Reader::readBytes(int numBytes, void *destination)
{
    log(MP4VerboseLevel::Full, "Will read "+to_string(numBytes)+" bytes with local location: "+to_string(m_currentLocation) +" and global location: "+to_string(m_currentLocation+m_offset));
    memcpy(destination, &m_bytes[m_currentLocation], numBytes);
    m_currentLocation += numBytes;
}

string MP4Reader::readISO639()
{
    skipBytes(sizeof(unsigned short));
    return "";
}

string MP4Reader::readUTF8(int length) {
    // TODO: Use http://utfcpp.sourceforge.net/

    //    char str[length+1];
    //    readBytes(length, str);
    //    str[length] = 0;
    return "";
}

void MP4Reader::readPString(unsigned int max) {
    unsigned char len;
    readBytes(1, &len);
    skipBytes(max-len-1);
}

std::string MP4Reader::read4Chars()
{
    char str[5];
    str[4] = 0; // terminate character
    readBytes(4*sizeof(char), str);
    log(MP4VerboseLevel::Full, "Read 4 chars: "+string(str));
    return string(str);
}

short MP4Reader::readShort()
{
    short n;
    readBytes(sizeof(short), &n);
    n = __builtin_bswap16(n);
    log(MP4VerboseLevel::Full, "Read 8: "+to_string(n));

    return n;
}

unsigned short MP4Reader::readUShort()
{
    unsigned short n;
    readBytes(sizeof(unsigned short), &n);
    n = __builtin_bswap16(n);
    log(MP4VerboseLevel::Full, "Read U16: "+to_string(n));

    return n;
}

char MP4Reader::readChar()
{
    char n;
    readBytes(sizeof(char), &n);
    n = __builtin_bswap32(n);
    log(MP4VerboseLevel::Full, "Read 8: "+to_string(n));

    return n;
}

unsigned char MP4Reader::readUChar()
{
    unsigned char n;
    readBytes(sizeof(unsigned char), &n);
    n = __builtin_bswap32(n);
    log(MP4VerboseLevel::Full, "Read U8: "+to_string(n));

    return n;
}

int MP4Reader::readInt()
{
    int n;
    readBytes(sizeof(int), &n);
    n = __builtin_bswap32(n);
    log(MP4VerboseLevel::Full, "Read 32: "+to_string(n));

    return n;
}

void MP4Reader::readUIntArray(int length, unsigned int *array)
{
    for(int i=0; i<length; i++) {
        readBytes(sizeof(unsigned int), &array[i]);
        array[i] = __builtin_bswap32(array[i]);
    }
}

void MP4Reader::readUCharArray(int length, unsigned char *array)
{
    for(int i=0; i<length; i++) {
        readBytes(sizeof(unsigned char), &array[i]);
        array[i] = __builtin_bswap32(array[i]);
    }
}

void MP4Reader::log(MP4VerboseLevel verboseLevel, string message)
{
    m_file->log(verboseLevel, message);
}

void MP4Reader::newBoxLength(unsigned int length)
{
    m_nextBoxAt = m_currentLocation + length - 8; // We have already used 8 bytes for the header
    // cout << "New box length: " << length << " giving next box at " << m_nextBoxAt << endl;
}

void MP4Reader::skipRemainingBytes() {
    unsigned int bytesLeftInBox = remainingBytes();
#ifdef MP4DEBUG
    cout << "Skipping the remaining " << bytesLeftInBox << " bytes in this atom." << endl;
#endif
    skipBytes(bytesLeftInBox);
}

unsigned int MP4Reader::remainingBytes()
{
    assert( (int(m_nextBoxAt) - int(m_currentLocation))  >=0 && "Remaining bytes is negative, should not happen.");

    return m_nextBoxAt - m_currentLocation;
}

MP4Reader *MP4Reader::subReader(MP4Box *parent)
{
    // Create a new subreader with a depth increased by one
    MP4Reader *subReader = new MP4Reader(&m_bytes[m_currentLocation], remainingBytes(), m_currentLocation+m_offset, m_file, m_readerDepth+1, parent);
    return subReader;
}

float MP4Reader::readFP16()
{
    int n = readInt();
    log(MP4VerboseLevel::Full, "Read FP8: "+to_string(float(n)/65536.0f));
    return float(n)/65536.0f;
}

float MP4Reader::readFP8()
{
    short n = readShort();
    log(MP4VerboseLevel::Full, "Read FP8: "+to_string(float(n)/256.0f));
    return float(n)/256.0f;
}

unsigned int MP4Reader::readUInt()
{
    unsigned int n;
    readBytes(sizeof(unsigned int), &n);
    n = __builtin_bswap32(n);
    log(MP4VerboseLevel::Full, "Read U32: "+to_string(n));

    return n;
}
