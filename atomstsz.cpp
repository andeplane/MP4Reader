#include "atomstsz.h"
#include "mp4reader.h"

AtomSTSZ::AtomSTSZ()
{
    m_name = "Sample Size Box (STSZ)";
}

void AtomSTSZ::readThisBox()
{
    fullheader = readFullHeader();
    sampleSize = m_reader->readUInt();
    unsigned int count = m_reader->readUInt();
    if(sampleSize==0) {
        for(unsigned int i=0; i<count; i++) {
            table.push_back(m_reader->readUInt());
        }
    }
}
