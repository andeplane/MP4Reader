#ifndef ATOMMVHD_H
#define ATOMMVHD_H
#include "mp4box.h"

class AtomMVHD : MP4Box
{
public:
    AtomMVHD();

    FullHeader fullheader;
    unsigned int creatonTime;
    unsigned int modificationTime;
    unsigned int timeScale;
    unsigned int duration;
    float    volume;
    unsigned int matrix[9];
    unsigned int nextTrackId;
};

#endif // ATOMMVHD_H
