#ifndef ATOMSTSZ_H
#define ATOMSTSZ_H
#include "mp4box.h"

typedef vector<unsigned int> sampleSizeTable_t;

class AtomSTSZ : public MP4Box
{
public:
    AtomSTSZ();
    FullHeader fullheader;
    unsigned int sampleSize;
    sampleSizeTable_t table;

    void readThisBox();

};

#endif // ATOMSTSZ_H
