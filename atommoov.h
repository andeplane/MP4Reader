#ifndef ATOMMOOV_H
#define ATOMMOOV_H
#include "mp4box.h"

class AtomMOOV : public MP4Box
{
public:
    AtomMOOV();
    void readThisBox();
};

#endif // ATOMMOOV_H
