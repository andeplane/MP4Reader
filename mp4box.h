#ifndef MP4BOX_H
#define MP4BOX_H
#include <iostream>
#include <vector>
#include <string>
#include <map>

#define U16 sizeof(unsigned short)
#define U32 sizeof(unsigned int)
#define FP16 32
#define FP8 16
#define ISO639 16
#define UTF8 8

 class AtomFTYP; class AtomMOOV; class AtomMVHD; class AtomTRAK; class AtomTKHD; class AtomMDIA;
 class AtomMDHD; class AtomHDLR; class AtomMINF; class AtomSTBL; class AtomSTSD; class AtomAVC1;
 class AtomAVCC; class AtomBTRT; class AtomSTTS; class AtomSTSS; class AtomSTSC; class AtomSTSZ;
 class AtomSTCO; class AtomSMHD; class AtomESDS; class AtomMDAT; class AtomMP4A;

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::map;

struct FullHeader {
    unsigned char version;
    unsigned char flags[3];
};

class MP4Reader;

class MP4Box
{
protected:
    unsigned int    m_length;
    string          m_type;
    string          m_name;
    MP4Box         *m_parent;
    vector<MP4Box*> m_children;
    MP4Reader      *m_reader;

    FullHeader readFullHeader();
    void readRemainingBoxes();
    virtual void readThisBox();
public:
    static MP4Box *readBox(MP4Reader *reader, MP4Box *parent);
    MP4Box();
    MP4Box(string name);
    void setup(MP4Reader *reader, unsigned int length, string type, MP4Box *parent);

    string type() { return m_type; }
    string name() { return m_name; }
    MP4Box *parent() { return m_parent; }

    void addChild(MP4Box *child);
    vector<MP4Box *> &children();
    vector<MP4Box*> findChildren(string type);
    MP4Box* findChild(string type, unsigned int index=0);
    MP4Box* findChildByPath(string path);
    AtomFTYP *FTYP() { return (AtomFTYP *)findChild("ftyp"); }
    AtomMOOV *MOOV() { return (AtomMOOV *)findChild("moov"); }
    AtomMVHD *MVHD() { return (AtomMVHD *)findChild("mvhd"); }
    AtomTRAK *TRAK() { return (AtomTRAK *)findChild("trak"); }
    AtomTKHD *TKHD() { return (AtomTKHD *)findChild("tkhd"); }
    AtomMDIA *MDIA() { return (AtomMDIA *)findChild("mdia"); }
    AtomMDHD *MDHD() { return (AtomMDHD *)findChild("mdhd"); }
    AtomHDLR *HDLR() { return (AtomHDLR *)findChild("hdlr"); }
    AtomMINF *MINF() { return (AtomMINF *)findChild("minf"); }
    AtomSTBL *STBL() { return (AtomSTBL *)findChild("stbl"); }
    AtomSTSD *STSD() { return (AtomSTSD *)findChild("stsd"); }
    AtomAVC1 *AVC1() { return (AtomAVC1 *)findChild("avc1"); }
    AtomAVCC *AVCC() { return (AtomAVCC *)findChild("avcc"); }
    AtomBTRT *BTRT() { return (AtomBTRT *)findChild("btrt"); }
    AtomSTTS *STTS() { return (AtomSTTS *)findChild("stts"); }
    AtomSTSS *STSS() { return (AtomSTSS *)findChild("stss"); }
    AtomSTSC *STSC() { return (AtomSTSC *)findChild("stsc"); }
    AtomSTSZ *STSZ() { return (AtomSTSZ *)findChild("stsz"); }
    AtomSTCO *STCO() { return (AtomSTCO *)findChild("stco"); }
    AtomSMHD *SMHD() { return (AtomSMHD *)findChild("smhd"); }
    AtomMP4A *MP4A() { return (AtomMP4A *)findChild("mp4a"); }
    AtomESDS *ESDS() { return (AtomESDS *)findChild("esds"); }
    AtomMDAT *MDAT() { return (AtomMDAT *)findChild("mdat"); }
};

#endif // MP4BOX_H
