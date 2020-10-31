#include <iostream>

#include "static/Hello.h"
#include "yaml-cpp/yaml.h"
#include <fstream>

void Hello::print()
{
    std::cout << "Hello Headers!" << std::endl;
}

void Mugo::downloader(std::string url)
{

    // list of ytdl channels/videos to download from
    std::vector<std::string> download_list;

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

    // print info
    print_info(*this);

    // run download command
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
        std::cout << "downloading " << i + 1 << "/" << download_list.size() << std::endl;

        // run command
        system(str_cmd);
    }

    // post download command
    post_download_cmd(this->post_download_commands, this->command_num, this->logfile);
}

int number_of_lines(std::string file)
{
    std::ifstream myfile(file);

    // new lines will be skipped unless we stop it from happening:
    myfile.unsetf(std::ios_base::skipws);

    // count the newlines with an algorithm specialized for counting:
    unsigned line_count = std::count(
        std::istream_iterator<char>(myfile),
        std::istream_iterator<char>(),
        '\n');

    return line_count;
}

bool find_file(std::string file)
{

    DIR *directory;   // creating pointer of type dirent
    struct dirent *x; // pointer represent directory stream
    // std::cout << "Please enter file name with its extension" << std::endl;
    // std::string s;       //declaring string variable
    // std::cin >> s;       // taking string as input or file name with input

    bool result = false; //declaring string variable and assign it to false.
    if ((directory = opendir(".")) != NULL)
    { // check if directory  open

        while ((x = readdir(directory)) != NULL)
        {

            {

                if (file == x->d_name)
                {
                    result = true; //if file found then  assign  result to false.

                    break; // break the loop if file found.
                }
            }
        }

        closedir(directory); //close directory....
    }
    if (result) // if file is present then....
    {
        return true;
    }
    else //if file is not present....
    {
        return false;
    }
}

void post_download_cmd(std::string *commands, int command_num, std::string logfile)
{
    // run post download commands
    if (commands)
    {
        std::vector<std::string> command_list;

        command_list.assign(commands, commands + command_num);

        for (int i = 0; i < command_list.size(); i++)
        {
            std::cout << "running command: " << command_list[i].c_str() << std::endl;

            std::string command_with_log = command_list[i] + " >> " + logfile;
            system(command_with_log.c_str());
        }

        if (!logfile.empty())
        {
            std::cout << "log saved to " << logfile << std::endl;
        }
    }
    else
    {
        std::cout << "No post download commands found" << std::endl;
    }
}

void print_info(Mugo mugo)
{
    if (!mugo.logfile.empty())
        std::cout << "logfile: " << mugo.logfile << std::endl;
    if (!mugo.archive.empty())
        std::cout << "archive: " << mugo.archive << std::endl;
    if (!mugo.download_dir.empty())
        std::cout << "download directory: " << mugo.download_dir << std::endl;
    if (mugo.channel_num > 0)
        std::cout << "number of channels: " << mugo.channel_num << std::endl;
    if (mugo.command_num > 0)
    {
        for (int i = 0; i < mugo.command_num; i++)
        {
            std::cout << "post download command " << i << ": " << mugo.post_download_commands[i] << std::endl;
            /* code */
        }
    }
}