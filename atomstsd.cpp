#include "atomstsd.h"

AtomSTSD::AtomSTSD()
{
    m_name = "Sample Description Box (STSD)";
}

void AtomSTSD::readThisBox()
{
    fullheader = readFullHeader();
    m_reader->skipBytes(sizeof(unsigned int)); // unsigned int entries = m_reader->readUInt(); // Not used?
    readRemainingBoxes();
}
