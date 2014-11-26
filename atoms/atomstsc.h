#ifndef ATOMSTSC_H
#define ATOMSTSC_H
#include "mp4box.h"
#include <map>
using namespace std;

class AtomSTSC : public MP4Box
{
public:
    AtomSTSC();
    FullHeader fullheader;
    vector<map<string, unsigned int> > table;
    void readThisBox();
};

#endif // ATOMSTSC_H
