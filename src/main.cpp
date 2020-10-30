#include <iostream>
#include <fstream>

#include "static/Hello.h"
#include "argh.h"

using namespace std;

int main(int argc, char *argv[])
{

    string config_file = "config.yaml";

    // exit if no config file found
    if (!find_file(config_file))
    {
        cout << "no config file found, please create a 'config.yaml' and run this command in the same dir";
        return EXIT_SUCCESS;
    }
    
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
            // get number of songs
            int line_count = number_of_lines(config.archive);
            std::cout << "Archived songs: " << line_count << "\n";
        }

        // clean up
        if (cmdl[{"-C", "--clean"}])
        {
            if (config.download_dir.empty())
            {
                cout << "No download dir found in config file" << endl;
                return EXIT_SUCCESS;
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