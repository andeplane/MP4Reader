#include "atommdat.h"
#include "mp4reader.h"

AtomMDAT::AtomMDAT()
{
    m_name = "Media Data Box (MDAT)";
}

void AtomMDAT::readThisBox()
{
    data.resize(m_reader->remainingBytes());
    m_reader->readBytes(data.size(), &data.front());
}
