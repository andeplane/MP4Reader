#ifndef ATOMAVC1_H
#define ATOMAVC1_H
#include "mp4box.h"

class AtomAVC1 : public MP4Box
{
public:
    AtomAVC1();
    unsigned short dataReferenceIndex;
    unsigned short width;
    unsigned short height;
    float horizontalResolution;
    float verticalResolution;
    unsigned short frameCount;
    string compressorName;
    unsigned short depth;
    unsigned short colorTableId;

    void readThisBox();
};

#endif // ATOMAVC1_H
