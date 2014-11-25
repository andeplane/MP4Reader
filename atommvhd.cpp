#include "atommvhd.h"
#include "mp4reader.h"
#include <cassert>

AtomMVHD::AtomMVHD()
{
}

void AtomMVHD::readThisBox()
{
    fullheader = readFullHeader();
    assert(fullheader.version == 0);
    creatonTime = m_reader->readUInt();
    modificationTime = m_reader->readUInt();
    timeScale = m_reader->readUInt();
    duration = m_reader->readUInt();
    rate = m_reader->readFP16();
    volume = m_reader->readFP8();

    m_reader->skipBytes(10);
    m_reader->readUIntArray(9, matrix);
    m_reader->skipBytes(6*4);
    nextTrackId = m_reader->readUInt();
}
