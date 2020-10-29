#include <iostream>

#include "static/Hello.h"
#include "yaml-cpp/yaml.h"

void Hello::print()
{
    std::cout << "Hello Headers!" << std::endl;
}

void Mugo::downloader(std::string url)
{

    std::vector<std::string> download_list;

    // string has value download that only
    if (!url.empty())
    {
        download_list.insert(download_list.begin(), url);
    }
    else
    {
        download_list.assign(this->channels, this->channels + this->channel_num);
    }

    // if config file has channels download them
    if (this->archive.empty())
    {
        std::cout << "you dont have archive, saving to archive.txt" << std::endl;
        this->archive = std::string("archive.txt");
    }
    else
    {
        std::cout << "you have archive, saving to " << this->archive << std::endl;
    };

    for (int i = 0; i < download_list.size(); i++)
    {
        // ytdl command
        std::stringstream command;

        command << R"(youtube-dl --add-metadata \
       --metadata-from-title "%(artist)s - %(title)s" \
       --embed-thumbnail \
       --download-archive )" +
                       this->archive + R"( \
       --no-post-overwrites \
       -ciwx \
       --audio-format mp3 \
       -o ")" + this->download_dir +
                       R"(%(title)s.%(ext)s" )" +
                       download_list[i] + R"(>/dev/null 2>&1;
        test $? -gt 128 && break;)";

        // create char command with size of command
        char str_cmd[command.str().size() + 1];
        strcpy(str_cmd, command.str().c_str());

        // info
        std::cout << "downloading " << i << "/" << download_list.size() << std::endl;

        // run command
        system(str_cmd);
    }

    if (this->post_download_commands)
    {
        std::vector<std::string> command_list;

        command_list.assign(this->post_download_commands, this->post_download_commands + this->command_num);
        // std::cout << this->command_num << std::endl;

        for (int i = 0; i < command_list.size(); i++)
        {
            std::cout << "running command: " << command_list[i].c_str() << std::endl;

            std::string command_with_log = command_list[i] + " >> " + (std::string)this->logfile;
            system(command_with_log.c_str());
        }
    }
}
