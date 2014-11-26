#ifndef ATOMESDS_H
#define ATOMESDS_H
#include "mp4box.h"

class AtomESDS : public MP4Box
{
public:
    AtomESDS();
    FullHeader fullheader;
    void readThisBox();
};

#endif // ATOMESDS_H
