#ifndef ATOMSTCO_H
#define ATOMSTCO_H
#include "mp4box.h"

class AtomSTCO : public MP4Box
{
public:
    AtomSTCO();
    FullHeader fullheader;
    vector<unsigned int> table;
    void readThisBox();
};

#endif // ATOMSTCO_H
