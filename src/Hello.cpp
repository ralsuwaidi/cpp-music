#include <iostream>

#include "static/Hello.h"
#include "yaml-cpp/yaml.h"


void Hello::print()
{
    std::cout << "Hello Headers!" << std::endl;
}

void Mugo::yt_download(std::string url)
{

    std::stringstream command;

    std::string myarchive;
    myarchive = this->archive;

    if (myarchive.empty())
    {
        std::cout << "you dont have archive, saving to archive.txt" << std::endl;
        this->archive = std::string("archive.txt");
    }
    else
    {
        std::cout << "you have archive, saving to " << this->archive << std::endl;
    };

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
                   url + R"(;
        test $? -gt 128 && break;)";

    char str_cmd[command.str().size() + 1];
    strcpy(str_cmd, command.str().c_str());

    system(str_cmd);
}
