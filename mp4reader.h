#ifndef MP4READER_H
#define MP4READER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::map;

class MP4Box;
class MP4File;
class Track;
enum class MP4VerboseLevel { None = 0, Low = 1, Medium = 2, High = 3, Full = 4};

class MP4Reader
{
private:
    unsigned int      m_currentLocation;
    MP4File          *m_file;
    MP4Box           *m_topNode;
    char             *m_bytes;
    unsigned int      m_length;
    unsigned int      m_offset;
    unsigned int      m_nextBoxAt;
    unsigned int      m_readerDepth;
public:
    MP4Reader(char *bytes, unsigned int length, unsigned int offset, MP4File *file, unsigned int readerDepth, MP4Box *parent);
    unsigned int currentLocation() { return m_currentLocation; }
    unsigned int currentGlobalLocation() { return m_currentLocation+m_offset; }
    unsigned int offset() { return m_offset; }

    void readBoxes();
    void readHeader(unsigned int &length, string &type);
    void readBytes(int numBytes, void *destination);
    void skipBytes(int numBytes);
    int readInt();
    unsigned int readUInt();
    short readShort();
    unsigned short readUShort();
    char readChar();
    unsigned char readUChar();
    string read4Chars();
    void readPString(unsigned int max);
    string readUTF8(int length = 0);
    void readUIntArray(int length, unsigned int *array);
    void newBoxLength(unsigned int length);
    void skipRemainingBytes();
    unsigned int remainingBytes();
    MP4Reader *subReader(MP4Box *parent);
    float readFP8();
    float readFP16();
    string readISO639();
    void readUCharArray(int length, unsigned char *array);
    MP4Box *topNode() { return m_topNode; }
    MP4File *file() { return m_file; }
    unsigned int readerDepth() { return m_readerDepth; }
    void log(MP4VerboseLevel verboseLevel, string message);
};

#endif // MP4READER_H
