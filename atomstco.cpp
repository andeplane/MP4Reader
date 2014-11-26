#include "atomstco.h"
#include "mp4reader.h"

AtomSTCO::AtomSTCO()
{
    m_name = "Chunk Offset Box (STCO)";
}

void AtomSTCO::readThisBox()
{
    fullheader = readFullHeader();
    unsigned int count = m_reader->readUInt();
    for(unsigned int i=0; i<count; i++) {
        table.push_back(m_reader->readUInt());
    }
}
