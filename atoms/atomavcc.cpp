#include "atomavcc.h"
#include "mp4reader.h"
#include <cassert>

AtomAVCC::AtomAVCC()
{
    m_name = "AVC Configuration Box (AVCC)";
}

void AtomAVCC::readThisBox()
{
    configurationVersion = m_reader->readUChar();
    avcProfileIndication = m_reader->readUChar();
    profileCompatability = m_reader->readUChar();
    avcLevelIndication   = m_reader->readUChar();
    lengthSizeMinusOne   = m_reader->readUChar() & 3; // wtf
    // assert(lengthSizeMinusOne == 3); // i have no idea
    unsigned char count = m_reader->readUChar() & 31;
    vector<unsigned char> array;
    // Read SPS data
    for(unsigned char i=0; i<count; i++) {
        unsigned char arrayLength = m_reader->readUShort();
        array.resize(arrayLength);
        m_reader->readUCharArray(arrayLength, &array.front());
        sps.push_back(array);
    }
    // Read PPS data
    count = m_reader->readUChar() & 31;
    for(unsigned char i=0; i<count; i++) {
        unsigned char arrayLength = m_reader->readUShort();
        array.resize(arrayLength);
        m_reader->readUCharArray(arrayLength, &array.front());
        pps.push_back(array);
    }

    array.clear();
    m_reader->skipRemainingBytes();
}
