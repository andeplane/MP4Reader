#ifndef ATOMTKHD_H
#define ATOMTKHD_H
#include "mp4box.h"

class AtomTKHD : public MP4Box
{
public:
    AtomTKHD();
    FullHeader fullheader;
    unsigned int creatonTime;
    unsigned int modificationTime;
    unsigned int trackId;
    unsigned int duration;
    unsigned short layer;
    unsigned short alternateGroup;
    unsigned int matrix[9];
};

#endif // ATOMTKHD_H
