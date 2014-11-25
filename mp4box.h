#ifndef MP4BOX_H
#define MP4BOX_H
#include <vector>
#include <string>

#define U16 sizeof(unsigned short)
#define U32 sizeof(unsigned int)
#define FP16 32
#define FP8 16
#define ISO639 16
#define UTF8 8

using std::vector;
using std::string;

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

    virtual void readThisBox() { }
    FullHeader readFullHeader();
    int remainingBytes();
    void readRemainingBoxes();
public:
    MP4Box();
    MP4Box(string name);
    void setup(MP4Reader *reader, unsigned int length, string type, MP4Box *parent);
    static MP4Box *readBox(MP4Reader *reader, MP4Box *parent);
    vector<MP4Box *> &children();
    void addChild(MP4Box *child);

};

#endif // MP4BOX_H
