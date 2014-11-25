#include "atomstbl.h"

AtomSTBL::AtomSTBL()
{
    m_name = "Sample Table Box (STBL)";
}

void AtomSTBL::readThisBox()
{
    readRemainingBoxes();
}
