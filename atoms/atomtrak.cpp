#include "atomtrak.h"
#include "mp4reader.h"
#include "mp4file.h"
#include "track.h"

AtomTRAK::AtomTRAK()
{
    m_name = "Track Box (TRAK)";
}

void AtomTRAK::readThisBox()
{
    readRemainingBoxes();
    Track *track = new Track(m_reader->file(), this);
    m_reader->file()->addTrack(track);
}
