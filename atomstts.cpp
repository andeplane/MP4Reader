#include "atomstts.h"
#include "mp4reader.h"

AtomSTTS::AtomSTTS()
{
    m_name = "Decoding Time to Sample Box (STTS)";
}

void AtomSTTS::readThisBox()
{
    fullheader = readFullHeader();
    unsigned int rows = m_reader->readUInt();
    for(int i=0; i<rows; i++) {
        map<string, unsigned int> row;
        row["delta"] = m_reader->readUInt();
        row["count"] = m_reader->readUInt();
        table.push_back(row);
    }
}
