#include "atommoov.h"

AtomMOOV::AtomMOOV()
{
    m_name = "Movie Box (MOOV)";
}

void AtomMOOV::readThisBox()
{
    readRemainingBoxes();
}
