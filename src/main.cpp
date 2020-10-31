#include <iostream>
#include <fstream>

#include "static/Hello.h"
#include "argh.h"

using namespace std;

int main(int argc, char *argv[])
{

    argh::parser cmdl(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

    string config_file = "config.yaml";

    if (!cmdl("--config").str().empty())
        config_file = cmdl("--config").str();

    // exit if no config file found
    while (!find_file(config_file))
    {

        cout << "no config file '" << config_file << "' found, please create a config file and run this command" << endl;

        cout << "please enter config file name" << endl;

        cin >> config_file;
        cout << config_file << endl;
    }

    // get configuration from yaml file
    Mugo config(config_file);

    // parse input
    if (argc > 1)
    {

        if (cmdl[{"-c", "--channels"}])
            std::cout << "Number of channels are: " << config.channel_num << endl;

        if (cmdl[{"-s", "--songs"}])
        {
            if (!config.archive.empty())
            {
                // get number of songs
                int line_count = number_of_lines(config.archive);
                std::cout << "Archived songs: " << line_count << "\n";
            }
            else
            {
                cout << "no config file found" << endl;
            }
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

                // extension files to delete
                string ext_delete[4] = {"*.tmp", "*.webm", "*.jpg", "*.webp"};

                for (const string &ext : ext_delete)
                {
                    string delete_command = "rm -r " + config.download_dir + ext + " > /dev/null 2>&1";
                    system(delete_command.c_str());
                }
            }
        }

        if (cmdl[{"-p", "--post_download"}])
        {
            if (!(config.post_download_commands->empty()))
            {
                post_download_cmd(config.post_download_commands, config.command_num, config.logfile);
            }
            else
            {
                cout << "No post download command found in config" << endl;
            }
        }
        if (!cmdl("--download").str().empty())
        {

            config.downloader(cmdl("--download").str());
        }
    }
    else
    {
        config.downloader("");
    }

    return EXIT_SUCCESS;
}