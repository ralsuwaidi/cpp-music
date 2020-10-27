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

    if (!url.empty())
    {
        download_list.insert(download_list.begin(),url);
    }
    else
    {
        download_list.assign(this->channels, this->channels + this->channel_num);
    }

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
                       download_list[i] + R"(;
        test $? -gt 128 && break;)";

        char str_cmd[command.str().size() + 1];
        strcpy(str_cmd, command.str().c_str());

        system(str_cmd);
    }

    if(this->post_download_commands){

        for (int i = 0; i < this->post_download_commands->size(); i++)
        {
            system(this->post_download_commands[i].c_str());
        }
        
    }

}
