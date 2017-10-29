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

#define X_POSITION1 0
#define Y_POSITION1 1
#define Z_POSITION1 2
#define X_ROTATION1 3
#define Y_ROTATION1 4
#define Z_ROTATION1 5

class JointLoader
{

public:

// OFFSET


    double offsetX, offsetY , offsetZ;

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
    std::vector<int> channels1;

    // channels
    void Channels(std::ifstream& infile);


    std::vector<JointLoader> childjoints;
    std::string name;

    bool is_root;
    bool is_end;


    JointLoader(bool root = false, bool end = false)
    {
        is_root=root;
        is_end=end;
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



    void outp(std::ofstream& outfile,const char *offset = "\0" );


};



#endif
