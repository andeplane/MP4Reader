#ifndef ATOMSMHD_H
#define ATOMSMHD_H
#include "mp4box.h"

class AtomSMHD : public MP4Box
{
public:
    AtomSMHD();
    FullHeader fullheader;
    float balance;

    void readThisBox();
};

#endif // ATOMSMHD_H
