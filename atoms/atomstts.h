#ifndef ATOMSTTS_H
#define ATOMSTTS_H
#include "mp4box.h"
#include <map>
using std::map;

class AtomSTTS : public MP4Box
{
public:
    AtomSTTS();
    FullHeader fullheader;
    vector<map<string, unsigned int> > table;

    void readThisBox();
};

#endif // ATOMSTTS_H
