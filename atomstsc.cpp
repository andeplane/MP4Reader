#include "atomstsc.h"
#include "mp4reader.h"

AtomSTSC::AtomSTSC()
{
    m_name = "Sample to Chunk Box (STSC)";
}

void AtomSTSC::readThisBox()
{
    fullheader = readFullHeader();
    unsigned int rows = m_reader->readUInt();
    for(int i=0; i<rows; i++) {
        map<string, unsigned int> row;
        row["firstChunk"] = m_reader->readUInt();
        row["samplesPerChunk"] = m_reader->readUInt();
        row["sampleDescriptionId"] = m_reader->readUInt();
    }
}

