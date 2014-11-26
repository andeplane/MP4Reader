#ifndef ATOMBTRT_H
#define ATOMBTRT_H
#include "mp4box.h"

class AtomBTRT : public MP4Box
{
public:
    AtomBTRT();
    unsigned int bufferSizeDb;
    unsigned int maxBitrate;
    unsigned int avgBitrate;

    void readThisBox();
};

#endif // ATOMBTRT_H
