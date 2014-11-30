#include "track.h"

Track::Track(MP4File *file, AtomTRAK *trak)
{
    this->file = file;
    this->trak = trak;
}

unsigned int Track::getTrackId()
{
    return trak->TKHD()->trackId;
}

sampleSizeTable_t Track::getSampleSizeTable()
{
    AtomSTSZ *stsz = (AtomSTSZ*)trak->findChildByPath("mdia.minf.stbl.stsz");
    assert(stsz != 0 && "Could not find STSZ in path trak.mdia.minf.stbl.stsz");
    return stsz->table;
}

unsigned int Track::getSampleCount()
{
    return getSampleSizeTable().size();
}
