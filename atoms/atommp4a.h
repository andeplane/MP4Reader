#ifndef ATOMMP4A_H
#define ATOMMP4A_H
#include "mp4box.h"

class AtomMP4A : public MP4Box
{
public:
    AtomMP4A();
    unsigned short dataReferenceIndex;
    unsigned short version;
    unsigned short channelCount;
    unsigned short sampleSize;
    unsigned short compressionId;
    unsigned short packetSize;
    unsigned short sampleRate;
    void readThisBox();
};

#endif // ATOMMP4A_H
