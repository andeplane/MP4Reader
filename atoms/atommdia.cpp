#include "atommdia.h"

AtomMDIA::AtomMDIA()
{
    m_name = "Media Box (MDIA)";
}

void AtomMDIA::readThisBox()
{
    readRemainingBoxes();
}
