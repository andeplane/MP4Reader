#ifndef ATOMMDHD_H
#define ATOMMDHD_H
#include "mp4box.h"

class AtomMDHD : public MP4Box
{
public:
    AtomMDHD();
    FullHeader fullheader;
    unsigned int creationTime;
    unsigned int modificationTime;
    unsigned int timeScale;
    unsigned int duration;

    void readThisBox();
};

#endif // ATOMMDHD_H
