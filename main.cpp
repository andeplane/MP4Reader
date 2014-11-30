#include <iostream>
#include "mp4reader.h"
#include "mp4file.h"
#include "atoms/atoms.h"

using namespace std;

int main()
{
    MP4File file("kateWeb.mp4", -1);
    file.setVerboseLevel(MP4VerboseLevel::Low);
    file.setLogToScreen(true);
    file.read();
    AtomTRAK *trak = (AtomTRAK *)file.findNodeByPath("moov.trak");
    cout << trak->name() << endl;

    cout << "Hello World!" << endl;
    return 0;
}

