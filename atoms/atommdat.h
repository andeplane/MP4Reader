#ifndef ATOMMDAT_H
#define ATOMMDAT_H
#include "mp4box.h"

class AtomMDAT : public MP4Box
{
public:
    AtomMDAT();
    void readThisBox();
    vector<unsigned char> data;
};

#endif // ATOMMDAT_H
