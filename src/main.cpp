#include <iostream>

#include "static/Hello.h"
#include "yaml-cpp/yaml.h"

using namespace std;

int main()
{
    Mugo test("config.yaml");
    cout << "Number of .a in build is " << test.channels[0] << endl;

    cout << test.hasYDL;

    return 0;
}