#include "mp4box.h"
#include "mp4reader.h"
#include "atoms/atoms.h"

#include <sstream>
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
    reader->newBoxLength(16); // The function will subtract 8 for the headerbytes, but currently, the total 8 bytes might be everything, so this will add a total of 8 bytes until the next header.
    unsigned int length;
    string type;
    reader->readHeader(length, type);
    reader->newBoxLength(length);
    MP4Box *box;

    vector<string> supportedExtraAtoms = {"iods", "edts", "vmhd", "dinf", "udta", "free"};

#ifdef MP4DEBUG
        cout << "Read a box of type " << type << " with length " << length << " and offset " << reader->currentLocation() + reader->offset() - 8<< endl;
#endif

    if(type.compare(string("ftyp")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomFTYP with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomFTYP();
    } else if(type.compare(string("moov")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomMOOV with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomMOOV();
    } else if(type.compare(string("mvhd")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomMVHD with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomMVHD();
    } else if(type.compare(string("trak")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomTRAK with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomTRAK();
    } else if(type.compare(string("tkhd")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomTKHD with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomTKHD();
    } else if(type.compare(string("mdia")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomMDIA with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomMDIA();
    } else if(type.compare(string("mdhd")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomMDHD with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomMDHD();
    } else if(type.compare(string("hdlr")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomHDLR with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomHDLR();
    } else if(type.compare(string("minf")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomMINF with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomMINF();
    } else if(type.compare(string("stbl")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomSTBL with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomSTBL();
    } else if(type.compare(string("stsd")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomSTSD with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomSTSD();
    } else if(type.compare(string("avc1")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomAVC1 with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomAVC1();
    } else if(type.compare(string("avcC")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomAVCC with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomAVCC();
    } else if(type.compare(string("btrt")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomBTRT with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomBTRT();
    } else if(type.compare(string("stts")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomSTTS with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomSTTS();
    } else if(type.compare(string("stss")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomSTSS with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomSTSS();
    } else if(type.compare(string("stsc")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomSTSC with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomSTSC();
    } else if(type.compare(string("stsz")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomSTSZ with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomSTSZ();
    } else if(type.compare(string("stco")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomSTCO with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomSTCO();
    } else if(type.compare(string("smhd")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomSMHD with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomSMHD();
    } else if(type.compare(string("mp4a")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomMP4A with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomMP4A();
    } else if(type.compare(string("esds")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomESDS with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomESDS();
    } else if(type.compare(string("mdat")) == 0) {
        reader->log(MP4VerboseLevel::Medium, "Creating AtomMDAT with length "+to_string(length)+" and offset "+to_string(reader->currentLocation() + reader->offset() - 8));
        box = new AtomMDAT();
    } else {
        if(std::find(supportedExtraAtoms.begin(), supportedExtraAtoms.end(), type) != supportedExtraAtoms.end()) {
            reader->log(MP4VerboseLevel::Medium, "Creating Atom"+type);
            box = new MP4Box(type);
        } else {
            cout << "Box of type " << type << " is not implemented yet, aborting! " << endl;
            exit(1);
        }
    }

    box->setup(reader, length, type, parent);
    cout << "Reading box of typwe " << type << endl;
    box->readThisBox();
#ifdef MP4DEBUG
    cout << "Finished with box of type " << type << endl;
#endif
    return box;
}

void MP4Box::addChild(MP4Box *child)
{
    m_children.push_back(child);
}

vector<MP4Box *> MP4Box::findChildren(string type)
{
    vector<MP4Box*> children;
    for(MP4Box *child : m_children) {
        if(type.compare(child->type()) == 0) {
            children.push_back(child);
        }
    }

    return children;
}

MP4Box *MP4Box::findChild(string type, unsigned int index)
{
    vector<MP4Box*> children = findChildren(type);
    if(children.size() > index) return children.at(index);
    else return 0;
}

MP4Box *MP4Box::findChildByPath(string path)
{
    // From http://stackoverflow.com/questions/19370078/split-the-string-on-dot-and-retrieve-each-values-from-it-in-c
    MP4Box *treeParent = this;

    std::istringstream iss(path);
    string token;
    while (getline(iss, token, '.')) {
        if (!token.empty()) {
            treeParent = treeParent->findChild(token);
            if(treeParent == 0) return 0; // We didn't find it
            // This is a part of the path
        }
    }

    return treeParent;
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
    // MP4Box::readBox(m_reader, this);
    delete reader;
    m_reader->skipRemainingBytes(); // These bytes are read in our sub reader
}
