#ifndef ATOMSTSZ_H
#define ATOMSTSZ_H
#include "mp4box.h"

class AtomSTSZ : public MP4Box
{
public:
    AtomSTSZ();
    FullHeader fullheader;
    unsigned int sampleSize;
    vector<unsigned int> table;

    void readThisBox();

};

#endif // ATOMSTSZ_H
