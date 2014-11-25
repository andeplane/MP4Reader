#ifndef ATOMTRAK_H
#define ATOMTRAK_H
#include "mp4box.h"

class AtomTRAK : public MP4Box
{
public:
    AtomTRAK();
    void readThisBox();
};

#endif // ATOMTRAK_H
