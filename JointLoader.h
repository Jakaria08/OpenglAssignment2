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
#include <glm/glm.hpp>


#define X_POSITION 0
#define Y_POSITION 1
#define Z_POSITION 2
#define X_ROTATION 3
#define Y_ROTATION 4
#define Z_ROTATION 5

class JointLoader
{

public:

// OFFSET


    double offsetX, offsetY , offsetZ;


    std::vector<int> channels;

    // channels
    void Channels(std::ifstream& infile);


    std::string name;

    bool is_root;
    bool is_end;

    JointLoader *parent;

    std::vector<JointLoader *> childjoints;


    JointLoader(bool root = false, bool end = false, JointLoader *parent=0)
    {
        is_root=root;
        is_end=end;
        this->parent = parent;
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

    const std::vector<JointLoader *> & get_children()
    {
        return childjoints;
    }

    bool has_children()
    {
        return childjoints.size() > 0 ;
    }

    const JointLoader * get_parent()
    {
        return parent;
    }



};



#endif
