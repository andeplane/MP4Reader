#ifndef ATOMFTYP_H
#define ATOMFTYP_H
#include "mp4box.h"

class AtomFTYP : public MP4Box
{
public:
    AtomFTYP();
    string majorBrand;
    unsigned int minorVersion;
    vector<string> compatibleBrands;
    void readThisBox();
};

#endif // ATOMFTYP_H
