#include "mp4box.h"
#include "mp4reader.h"
#include "atoms.h"

#include <algorithm>
#include <iostream>
using std::cout; using std::endl;

MP4Box::MP4Box() :
    m_length(0),
    m_type(""),
    m_name(""),
    m_parent(0),
    m_reader(0)
{

}

MP4Box::MP4Box(std::string name) :
    m_length(0),
    m_type(name),
    m_name(name),
    m_parent(0),
    m_reader(0)
{

}

void MP4Box::setup(MP4Reader *reader, unsigned int length, string type, MP4Box *parent)
{
    m_reader = reader;
    m_length = length;
    m_type = type;
    m_parent = parent;

    if(parent) parent->addChild(this);
}

MP4Box *MP4Box::readBox(MP4Reader *reader, MP4Box *parent)
{
    cout << endl << "Will read a new atom" << endl;
    reader->newBoxLength(16); // The function will subtract 8 for the headerbytes, but currently, the total 8 bytes might be everything, so this will add a total of 8 bytes until the next header.
    unsigned int length;
    string type;
    reader->readHeader(length, type);
    reader->newBoxLength(length);
    MP4Box *box;

    vector<string> supportedExtraAtoms = {"iods", "edts", "vmhd", "dinf"};

    if(type.compare(string("ftyp")) == 0) {
        cout << "Read a box of type FTYP with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        box = new AtomFTYP();
    } else if(type.compare(string("moov")) == 0) {
        cout << "Read a box of type MOOV with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        box = new AtomMOOV();
    } else if(type.compare(string("mvhd")) == 0) {
        cout << "Read a box of type MVHD with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        box = new AtomMVHD();
//    } else if(type.compare(string("iods")) == 0) {
//        cout << "Read a box of type IODS with length " << length << endl;
//        box = new MP4Box();
//        reader->skipRemainingBytes();
    } else if(type.compare(string("trak")) == 0) {
        cout << "Read a box of type TRAK with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        box = new AtomTRAK();
    } else if(type.compare(string("tkhd")) == 0) {
        cout << "Read a box of type TKHD with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        box = new AtomTKHD();
    } else if(type.compare(string("mdia")) == 0) {
        cout << "Read a box of type MDIA with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        box = new AtomMDIA();
    } else if(type.compare(string("mdhd")) == 0) {
        cout << "Read a box of type MDHD with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        box = new AtomMDHD();
    } else if(type.compare(string("hdlr")) == 0) {
        cout << "Read a box of type HDLR with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        box = new AtomHDLR();
    } else if(type.compare(string("minf")) == 0) {
        cout << "Read a box of type MINF with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        box = new AtomMINF();
    } else if(type.compare(string("stbl")) == 0) {
        cout << "Read a box of type STBL with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        box = new AtomSTBL();
    } else if(type.compare(string("stsd")) == 0) {
        cout << "Read a box of type STSD with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        box = new AtomSTSD();
    } else {
        if(std::find(supportedExtraAtoms.begin(), supportedExtraAtoms.end(), type) != supportedExtraAtoms.end()) {
            box = new MP4Box(type);
            cout << "Read a box of type " << type << " with length " << length << " and offset " << reader->currentLocation() + reader->offset() << endl;
        } else {
            cout << "Box of type " << type << " is not implemented yet, aborting! " << endl;
            exit(1);
        }
    }

    cout << "Calling setup" << endl;
    box->setup(reader, length, type, parent);
    box->readThisBox();
    cout << "Finished with box of type " << type << endl;
    return box;
}

void MP4Box::addChild(MP4Box *child)
{
    m_children.push_back(child);
}

vector<MP4Box *> &MP4Box::children()
{
    return m_children;
}

void MP4Box::readThisBox()
{
    m_reader->skipRemainingBytes();
}

FullHeader MP4Box::readFullHeader()
{
    FullHeader header;
    header.version = m_reader->readUChar();
    header.flags[0] = m_reader->readUChar();
    header.flags[1] = m_reader->readUChar();
    header.flags[2] = m_reader->readUChar();
    return header;
}

void MP4Box::readRemainingBoxes()
{
    MP4Reader *reader = m_reader->subReader(this);
    reader->readBoxes();
    MP4Box::readBox(m_reader, this);
    delete reader;
}

//void MP4Box::readFTYP() {
//    string majorBrand = read4Chars();
//    int minorVersion = readInt();
//    // int numberOfCompatibleBrands = (m_length - 16)/4;
//    // readBytes(numberOfCompatibleBrands * 4 * sizeof(char));

//    skipRemainingBytes();
//}

//void MP4Box::readMOOV() {
//    readRemainingBoxes();
//}

//void MP4Box::readMVHD() {
//    MVHD data;

//    data.fullheader = readFullHeader();
//    data.creatonTime = readUInt();
//    data.modificationTime = readUInt();
//    data.timeScale = readUInt();
//    data.duration = readUInt();
//    skipBytes(sizeof(unsigned int) + sizeof(short) + 10); // rate, volume and 10 bytes
//    readUIntArray(9, &data.matrix[0]);
//    skipBytes(6*4); // dunno why
//    data.nextTrackId = readUInt();
//}

//void MP4Box::readTRAK() {
//    readRemainingBoxes();
//}

//void MP4Box::readTKHD() {
//    TKHD data;

//    data.fullheader = readFullHeader();
//    data.creatonTime = readUInt();
//    data.modificationTime = readUInt();
//    data.trackId = readUInt();
//    skipBytes(4);
//    data.duration = readUInt();
//    skipBytes(8);
//    data.layer = readUShort();
//    data.alternateGroup = readUShort();
//    skipBytes(4);
//    readUIntArray(9, &data.matrix[0]);
//    skipBytes(8);
//}

//void MP4Box::readMDIA() {
//    readRemainingBoxes();
//}

//void MP4Box::readMDHD() {
//    readFullHeader();
//    skipBytes(20);
//}

//void MP4Box::readHDLR() {
//    readFullHeader();
//    skipBytes(8);
//    skipBytes(4*3);
//    int bytesLeft = m_length - 32;
//    if(bytesLeft > 0) {
//        skipBytes(bytesLeft);
//    }
//}

//void MP4Box::readMINF() {
//    readRemainingBoxes();
//}

//void MP4Box::readSTBL() {
//    readRemainingBoxes();
//}

//void MP4Box::readSTSD() {
//    readFullHeader();
//    skipBytes(4);
//    readRemainingBoxes();
//}

//void MP4Box::readAVC1() {
//    skipBytes(6 + 3*U16 + 3*U32 + 2*U16 + 2*FP16 + U32 + U16);
//    readPString();
//    skipBytes(2*U16);
//    readRemainingBoxes();
//}

//void MP4Box::readMP4A() {
//    skipBytes(6 + 2*U16 + 6 + 4*U16 + U32);
//    readRemainingBoxes();
//}

//void MP4Box::readESDS() {
//    readFullHeader();
//    skipRemainingBytes();
//}

//void MP4Box::readAVCC() {
//    cout << "AVCC" << endl;
//    exit(1);
//}

//void MP4Box::readBTRT() {
//    cout << "BTRT" << endl;
//    exit(1);
//}

//void MP4Box::readSTTS() {
//    cout << "STTS" << endl;
//    exit(1);
//}

//void MP4Box::readSTSS() {
//    cout << "STSS" << endl;
//    exit(1);
//}

//void MP4Box::readSTSZ() {
//    cout << "STSZ" << endl;
//    exit(1);
//}

//void MP4Box::readSTCO() {
//    cout << "STCO" << endl;
//    exit(1);
//}

//void MP4Box::readSMHD() {
//    cout << "SMHD" << endl;
//    exit(1);
//}

//void MP4Box::readMDAT() {
//    cout << "MDAT" << endl;
//    exit(1);
//}

//void MP4Box::defaultApproach() {
//    skipRemainingBytes();
//}
