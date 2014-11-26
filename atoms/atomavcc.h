#ifndef ATOMAVCC_H
#define ATOMAVCC_H
#include "mp4box.h"

class AtomAVCC : public MP4Box
{
public:
    AtomAVCC();
    unsigned char configurationVersion;
    unsigned char avcProfileIndication;
    unsigned char profileCompatability;
    unsigned char avcLevelIndication;
    unsigned char lengthSizeMinusOne;
    vector<vector<unsigned char> > sps;
    vector<vector<unsigned char> > pps;
    void readThisBox();
};

#endif // ATOMAVCC_H
