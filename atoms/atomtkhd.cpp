#include "atomtkhd.h"
#include "mp4reader.h"
#include <cassert>

AtomTKHD::AtomTKHD()
{
    m_name = "Track Header Box (TKHD)";
}

void AtomTKHD::readThisBox()
{
    fullheader = readFullHeader();
    assert(fullheader.version == 0);
    creatonTime = m_reader->readUInt();
    modificationTime = m_reader->readUInt();
    trackId = m_reader->readUInt();

    m_reader->skipBytes(4);

    duration = m_reader->readUInt();

    m_reader->skipBytes(8);

    layer = m_reader->readUShort();
    alternateGroup = m_reader->readUShort();
    volume = m_reader->readFP8();
    m_reader->skipBytes(2);
    m_reader->readUIntArray(9, matrix);
    width = m_reader->readFP16();
    height = m_reader->readFP16();
}


