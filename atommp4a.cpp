#include "atommp4a.h"
#include "mp4reader.h"

AtomMP4A::AtomMP4A()
{
    m_name = "MP4A";
}

void AtomMP4A::readThisBox()
{
    m_reader->skipBytes(6);
    dataReferenceIndex = m_reader->readUShort();
    version = m_reader->readUShort();
    m_reader->skipBytes(6);
    channelCount = m_reader->readUShort();
    sampleSize = m_reader->readUShort();
    compressionId = m_reader->readUShort();
    packetSize = m_reader->readUShort();
    sampleRate = (m_reader->readUInt() >> 16);
    readRemainingBoxes();
}
