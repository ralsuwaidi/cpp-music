#include <iostream>

#include "static/Hello.h"
#include "yaml-cpp/yaml.h"

void Hello::print()
{
    std::cout << "Hello Headers!" << std::endl;
}

void Mugo::download_new()
{
    int c;

    c = (int)system("which ls");

    if (c == 0)
    {
        std::cout << "file exists";
    }
    else
    {
        std::cout << "file doesnt exist";
    }
}