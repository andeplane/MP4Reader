#ifndef TRACK_H
#define TRACK_H
#include "atoms/atoms.h"
class MP4File;

class Track
{
public:
    MP4File *file;
    AtomTRAK *trak;
    Track(MP4File *file, AtomTRAK *trak);
    unsigned int getTrackId();
    sampleSizeTable_t getSampleSizeTable();
    unsigned int getSampleCount();
};

#endif // TRACK_H
