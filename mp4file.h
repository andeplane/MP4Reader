#ifndef MP4FILE_H
#define MP4FILE_H
#include "mp4reader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <map>

using std::string;
using std::ifstream;
using std::ofstream;
using std::map;

class Track;

class MP4File
{
private:
    string   m_filename;
    ifstream m_file;
    ofstream m_logFile;
    int      m_totalNumberOfBytes;
    char    *m_bytes;
    MP4Reader *m_reader;
    map<unsigned int, Track*> m_tracks;
    MP4VerboseLevel   m_verboseLevel;
    bool m_logToScreen;

    bool open();
    void ensureOpen();
    void readBytesFromFile(int numBytes);
public:
    MP4File(string filename, int totalNumberOfBytes);
    void read();
    MP4Reader *reader() { return m_reader; }
    MP4Box* findNodeByPath(string path);
    void addTrack(Track *track);
    bool setVerboseLevel(MP4VerboseLevel verboseLevel) { m_verboseLevel = verboseLevel; }
    MP4VerboseLevel verboseLevel() { return m_verboseLevel; }
    void log(MP4VerboseLevel verboseLevel, string message);
    bool logToScreen() const;
    void setLogToScreen(bool logToScreen);
};

#endif // MP4FILE_H
