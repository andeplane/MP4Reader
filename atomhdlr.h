#ifndef ATOMHDLR_H
#define ATOMHDLR_H
#include "mp4box.h"
#include "mp4reader.h"
#include <cassert>

class AtomHDLR : public MP4Box
{
public:
    AtomHDLR();
    FullHeader fullheader;
    string handlerType;

    void readThisBox();
};

#endif // ATOMHDLR_H
