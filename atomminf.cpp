#include "atomminf.h"

AtomMINF::AtomMINF()
{
    m_name = "Media Information Box (MINF)";
}

void AtomMINF::readThisBox()
{
    readRemainingBoxes();
}
