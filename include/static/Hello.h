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
        ydl = (int)system("which youtube-dl");
        ff = (int)system("which ffmpeg");

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

    void yt_download(std::string url);
};

int ext_number(std::string dir, std::string extension);

#endif