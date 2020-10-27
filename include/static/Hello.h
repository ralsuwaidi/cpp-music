#ifndef __HELLO_H__
#define __HELLO_H__

#include <string.h>
#include "yaml-cpp/yaml.h"

class Hello
{
public:
    void print();
};

class Mugo
{
public:
    int channel_num;
    std::string archive;
    std::string logfile;
    std::string *channels;
    std::string *post_download_commands;
    bool hasYDL;
    bool hasFF;
    std::string download_dir;

    // Mugo constructor
    Mugo(std::string file)
    {
        YAML::Node config = YAML::LoadFile(file);
        if (config["channels"])
        {
            channel_num = config["channels"].size();

            channels = new std::string[channel_num];
            for (int i = 0; i < channel_num; i++)
            {
                channels[i] = config["channels"][i].as<std::string>();
            };
        };

        if (config["post_download_commands"])
        {

            int command_size = config["post_download_commands"].size();
            post_download_commands = new std::string[command_size];
            for (int i = 0; i < command_size; i++)
            {
                post_download_commands[i] = config["post_download_commands"][i].as<std::string>();
            };
        };

        if (config["archive"])
        {
            archive = config["archive"].as<std::string>();
        }

        if (config["download_dir"])
        {
            download_dir = config["download_dir"].as<std::string>();
        }

        if (config["logfile"])
        {
            logfile = config["logfile"].as<std::string>();
        };

        // check if YDL exists
        int ydl, ff;
        ydl = (int)system("which youtube-dl > /dev/null 2>&1");
        ff = (int)system("which ffmpeg > /dev/null 2>&1");

        if (ydl == 0)
        {
            hasYDL = true;
        }
        else
        {
            hasYDL = false;
        }

        // check if ffmpeg exists
        if (ff == 0)
        {
            hasFF = true;
        }
        else
        {
            hasFF = false;
        }
    }

    void downloader(std::string url);
};

#endif