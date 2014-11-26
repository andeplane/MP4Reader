#include "atommdat.h"
#include "mp4reader.h"

AtomMDAT::AtomMDAT()
{
    m_name = "Media Data Box (MDAT)";
}

void AtomMDAT::readThisBox()
{
    data.resize(m_reader->remainingBytes());
    for(unsigned int i=0; i<data.size(); i++) {
        data[i] = m_reader->readUChar();
    }
}
