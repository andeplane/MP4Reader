#ifndef ATOMSTSS_H
#define ATOMSTSS_H
#include "mp4box.h"

class AtomSTSS : public MP4Box
{
public:
    AtomSTSS();
    FullHeader fullheader;
    vector<unsigned int> samples;
    void readThisBox();
    unsigned int numberOfSamples() { return samples.size(); }
};

#endif // ATOMSTSS_H
