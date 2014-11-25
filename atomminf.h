#ifndef ATOMMINF_H
#define ATOMMINF_H
#include "mp4box.h"

class AtomMINF : public MP4Box
{
public:
    AtomMINF();
    void readThisBox();
};

#endif // ATOMMINF_H
