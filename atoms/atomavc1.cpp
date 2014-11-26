#include "atomavc1.h"
#include "mp4reader.h"
#include <cassert>

AtomAVC1::AtomAVC1()
{
    m_name = "AVC1";
}

void AtomAVC1::readThisBox()
{
  m_reader->skipBytes(6);
  dataReferenceIndex = m_reader->readUShort();
  assert(m_reader->readUShort()==0); // Version
  assert(m_reader->readUShort()==0); // Revision Level
  m_reader->readUInt(); // Vendor
  m_reader->readUInt(); // Temporal Quality
  m_reader->readUInt(); // Spatial Quality
  width = m_reader->readUShort();
  height = m_reader->readUShort();
  horizontalResolution = m_reader->readFP16();
  verticalResolution = m_reader->readFP16();
  m_reader->readUInt();
  frameCount = m_reader->readUShort();
  m_reader->readPString(32); // compressorName = TODO: Fix readPString
  depth = m_reader->readUShort();
  colorTableId = m_reader->readUShort();
  assert(colorTableId == 0xFFFF);
  readRemainingBoxes();
}
