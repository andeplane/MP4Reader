#ifndef ATOMSTBL_H
#define ATOMSTBL_H
#include "mp4box.h"

class AtomSTBL : public MP4Box
{
public:
    AtomSTBL();
    void readThisBox();
};

#endif // ATOMSTBL_H
