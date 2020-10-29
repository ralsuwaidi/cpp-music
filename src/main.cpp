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
    if (argc > 1)
    {
        argh::parser cmdl(argv);

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

        // clean up
        if (cmdl[{"-C", "--clean"}])
        {
            if (config.download_dir.empty())
            {
                cout << "No download dir found in config file" << endl;
            }
            else
            {

                string ext_delete[4] = {"*.tmp", "*.webm", "*.jpg", "*.webp"};


                for (const string &ext : ext_delete)
                {
                    string delete_command = "rm -r " + config.download_dir + ext + " > /dev/null 2>&1";
                    system(delete_command.c_str());
                }
            }
        }
    }
    else
    {
        config.downloader("");
    }

    return EXIT_SUCCESS;
}