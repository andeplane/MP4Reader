#include "atombtrt.h"
#include "mp4reader.h"

AtomBTRT::AtomBTRT()
{
    m_name = "Bit Rate Box (BTRT)";
}

void AtomBTRT::readThisBox()
{
    bufferSizeDb = m_reader->readUInt();
    maxBitrate = m_reader->readUInt();
    avgBitrate = m_reader->readUInt();
}
