#include <iostream>
#include "mp4reader.h"

using namespace std;

int main()
{
    MP4FileReader reader("kateWeb.mp4", -1);
    reader.read();

    cout << "Hello World!" << endl;
    return 0;
}

