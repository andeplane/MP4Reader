#include "mp4file.h"
#include "mp4reader.h"
#include "track.h"

MP4File::MP4File(string filename, int totalNumberOfBytes) :
    m_filename(filename),
    m_totalNumberOfBytes(totalNumberOfBytes),
    m_bytes(0),
    m_reader(0),
    m_verboseLevel(MP4VerboseLevel::None),
    m_logToScreen(false)
{
    m_logFile.open("mp4log.txt");
}

MP4Box *MP4File::findNodeByPath(std::string path)
{
    return m_reader->topNode()->findChildByPath(path);
}

void MP4File::addTrack(Track *track)
{
    m_tracks[track->getTrackId()] = track;
}

void MP4File::log(MP4VerboseLevel verboseLevel, string message)
{
    if(m_verboseLevel >= verboseLevel) {
        m_logFile << message << endl;
        if(m_logToScreen) {
            cout << message << endl;
        }
    }
}


bool MP4File::logToScreen() const
{
    return m_logToScreen;
}

void MP4File::setLogToScreen(bool logToScreen)
{
    m_logToScreen = logToScreen;
}
bool MP4File::open()
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

void MP4File::ensureOpen() {
    if(!m_file.is_open()) {
        cout << "File " << m_filename << " is not open, opening..." << endl;
        open();
    }
}

void MP4File::readBytesFromFile(int numBytes) {
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

void MP4File::read()
{
    readBytesFromFile(-1);
    cout << "Total number of bytes in file: " << m_totalNumberOfBytes << endl;
    m_reader = new MP4Reader(m_bytes, m_totalNumberOfBytes, 0, this, 0, 0);
    m_reader->readBoxes();
}
