#ifndef ATOMMVHD_H
#define ATOMMVHD_H
#include "mp4box.h"

class AtomMVHD : public MP4Box
{
public:
    AtomMVHD();

    FullHeader fullheader;
    unsigned int creatonTime;
    unsigned int modificationTime;
    unsigned int timeScale;
    unsigned int duration;
    float        volume;
    float        rate;
    unsigned int matrix[9];
    unsigned int nextTrackId;
    void readThisBox();
};

#endif // ATOMMVHD_H
