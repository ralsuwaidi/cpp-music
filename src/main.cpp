#include <iostream>

#include "static/Hello.h"
#include "yaml-cpp/yaml.h"

using namespace std;

int main()
{
    Mugo test("config.yaml");
    cout << "Number of .a in build is " << test.channels[0] << endl;

    if (test.hasYDL)
    {
        cout << "you have YDL" << endl;
    }

    if (test.hasFF)
    {
        cout << "you have FFMPEG" << endl;
    }


    test.yt_download("https://www.youtube.com/watch?v=-G8oXE3Q_dc");
    // cout << test.archive;

    return 0;
}