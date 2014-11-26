#include "atomsmhd.h"
#include "mp4reader.h"

AtomSMHD::AtomSMHD()
{
    m_name = "Sound Media Header Box (SMHD)";
}

void AtomSMHD::readThisBox()
{
    fullheader = readFullHeader();
    balance = m_reader->readFP8();
    m_reader->skipBytes(2);
}
