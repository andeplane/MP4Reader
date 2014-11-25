#ifndef ATOMMDIA_H
#define ATOMMDIA_H
#include "mp4box.h"

class AtomMDIA : public MP4Box
{
public:
    AtomMDIA();
    void readThisBox();
};

#endif // ATOMMDIA_H
