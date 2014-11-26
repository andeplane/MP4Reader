#ifndef ATOMSTSD_H
#define ATOMSTSD_H
#include "mp4box.h"
#include "mp4reader.h"

class AtomSTSD : public MP4Box
{
public:
    AtomSTSD();
    FullHeader fullheader;
    void readThisBox();
};

#endif // ATOMSTSD_H
