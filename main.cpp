#include <iostream>
#include "mp4reader.h"

using namespace std;

int main()
{
    MP4Reader reader("catvideo.mp4", -1);
    reader.readBoxes();

    cout << "Hello World!" << endl;
    return 0;
}

