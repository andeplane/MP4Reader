#include "atomhdlr.h"

AtomHDLR::AtomHDLR()
{
    m_name = "Handler Reference Box (HDLR)";
}

void AtomHDLR::readThisBox()
{
    fullheader = readFullHeader();
    m_reader->skipBytes(4);
    handlerType = m_reader->read4Chars();
    m_reader->skipBytes(4*3);
#ifdef MP4DEBUG
    cout << "HDLR: TODO: Read new box name instead of skipping";
#endif
    m_reader->skipRemainingBytes();
}
