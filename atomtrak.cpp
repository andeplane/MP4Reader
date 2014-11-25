#include "atomtrak.h"

AtomTRAK::AtomTRAK()
{
    m_name = "Track Box (TRAK)";
}

void AtomTRAK::readThisBox()
{
    readRemainingBoxes();
    cout << "TRAK: TODO: Create track objects" << endl;
}
