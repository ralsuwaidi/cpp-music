#include <iostream>
#include <fstream>

#include "static/Hello.h"
#include "argh.h"

using namespace std;

int main(int argc, char *argv[])
{
    string config_file = "config.yaml";
    // get configuration from yaml file
    Mugo config(config_file);

    // parse input
    if (argc > 0)
    {
        argh::parser cmdl(argv);

        if (cmdl[{"-v", "--verbose"}])
            std::cout << "Verbose, I am.\n";

        if (cmdl[{"-c", "--channels"}])
            std::cout << "Number of channels are: " << config.channel_num << endl;

        if (cmdl[{"-s", "--songs"}])
        {
            std::ifstream myfile(config.archive);

            // new lines will be skipped unless we stop it from happening:
            myfile.unsetf(std::ios_base::skipws);

            // count the newlines with an algorithm specialized for counting:
            unsigned line_count = std::count(
                std::istream_iterator<char>(myfile),
                std::istream_iterator<char>(),
                '\n');

            std::cout << "Archived songs: " << line_count << "\n";
        }
    }


    // test.yt_download("https://www.youtube.com/watch?v=-G8oXE3Q_dc");
    // cout << test.archive;

    return EXIT_SUCCESS;
}