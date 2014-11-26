#include "atomesds.h"
#include "mp4reader.h"

AtomESDS::AtomESDS()
{
    m_name = "Elementary Stream Descriptor (ESDS)";
}

void AtomESDS::readThisBox()
{
    fullheader = readFullHeader();
    m_reader->skipRemainingBytes();
}
