#include "atomstss.h"
#include "mp4reader.h"

AtomSTSS::AtomSTSS()
{
    m_name = "Sync Sample Box (STSS)";
}

void AtomSTSS::readThisBox()
{
    fullheader = readFullHeader();
    samples.resize(m_reader->readUInt());
    m_reader->readUIntArray(samples.size(), &samples.front());
}

