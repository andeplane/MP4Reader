#include "atommdhd.h"
#include "mp4reader.h"
#include <cassert>

AtomMDHD::AtomMDHD()
{
    m_name = "Media Header Box";
}

void AtomMDHD::readThisBox()
{
    fullheader = readFullHeader();
    assert(fullheader.version == 0);
    creationTime = m_reader->readUInt();
    modificationTime = m_reader->readUInt();
    timeScale = m_reader->readUInt();
    duration = m_reader->readUInt();
    m_reader->readISO639();
    m_reader->skipBytes(2);
}
