#include <iostream>
#include "mp4reader.h"
#include "atoms/atoms.h"

using namespace std;

int main()
{
    MP4FileReader reader("kateWeb.mp4", -1);
    reader.read();
    AtomTRAK *trak = (AtomTRAK *)reader.findNodeByPath("moov.trak");
    cout << trak->name() << endl;

    cout << "Hello World!" << endl;
    return 0;
}

