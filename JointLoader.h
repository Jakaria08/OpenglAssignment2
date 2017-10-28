#ifndef _JointLoader_h
#define _JointLoader_h

#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>

class JointLoader
{

public:

// OFFSET structure
    struct offset
    {
        double x, y , z;
    };
    offset o;

    // CHANNEL TYPES
    typedef enum
    {
        X_POSITION = 0,
        Y_POSITION,
        Z_POSITION,
        X_ROTATION,
        Y_ROTATION,
        Z_ROTATION
    } ChannelType;

    // ChannelVector
    std::vector<ChannelType> channels;

    // channels
    void read_channels(std::ifstream& infile);


    std::vector<JointLoader> childjoints;
    std::string name;

    bool is_root = false;
    bool is_end = true;

    JointLoader(/*bool root = false, bool end = false*/)
    {
        //is_root=root;
        //is_end=end;
        //this->o.x = this->o.y = this->o.z = 0;
    }


    bool load(std::ifstream& infile);
    // For trimming string
    std::string delUnnecessary(std::string &str)
    {
        int size = str.length();
        for(int j = 0; j<=size; j++)
        {
            for(int i = 0; i <=j; i++)
            {
                if(str[i] == ' ' && str[i+1] == ' ')
                {
                    str.erase(str.begin() + i);
                }
                else if(str[0]== ' ')
                {
                    str.erase(str.begin());
                }
                else if(str[i] == '\0' && str[i-1]== ' ')
                {
                    str.erase(str.end() - 1);
                }
            }
        }
        return str;
    }


    void set_offset(const double x, const double y, const double z)
    {
        this->o.x = x;
        this->o.y = y;
        this->o.z = z;
    }


    void print(std::ofstream& outfile,const char *offset = "\0" );


};



#endif
