#ifndef MP4READER_H
#define MP4READER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
class MP4Box;

class MP4Reader
{
private:
    string   m_filename;
    ifstream m_file;
    unsigned int      m_currentLocation;
    int      m_totalNumberOfBytes;
    unsigned int      m_nextBoxAt;
    vector<char> m_bytes;
    MP4Box  *m_topNode;

    bool open();
    void ensureOpen();
    void readBytesFromFile(int numBytes);
public:
    MP4Reader(string filename, int totalNumberOfBytes);
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
    void readPString();
    string readUTF8(int length);
    void readUIntArray(int length, unsigned int *array);
    void newBoxLength(unsigned int length);
    void skipRemainingBytes();
};

#endif // MP4READER_H
