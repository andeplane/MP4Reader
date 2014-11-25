#include "atomftyp.h"
#include "mp4reader.h"

AtomFTYP::AtomFTYP()
{

}

void AtomFTYP::readThisBox()
{
    majorBrand = m_reader->read4Chars();
    minorVersion = m_reader->readInt();
    int numberOfCompatibleBrands = (m_length - 16)/4;
    cout << "We found " << numberOfCompatibleBrands << " compatible brands" << endl;
    m_reader->skipBytes(numberOfCompatibleBrands * 4 * sizeof(char));
}
