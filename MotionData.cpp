#include "MotionData.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>


using namespace std;

void MotionData::loadMotion(ifstream& infile)
{

        string line;

        infile >> line;

        cout << line;
        if (line == "Frames:")
        {
            infile >> this->frames;
            cout <<this->frames;
        }

        infile >> line;

        if(line == "Frame")
        {
            infile >> line;
            infile >> this->frametime;
            cout <<this->frametime;
        }

        fr_set.resize(this->frames);

        for(int i = 0; i < this->frames; i++ )
        {

            double frameDat;

            for( int j = 0; j < this->total_frame_size; j++ )
            {
                infile >> frameDat;
                fr_set[i].push_back(frameDat);
            }
        }
    }


void MotionData::OutputMotion(std::ofstream& Outputfile)
{


    Outputfile << fixed << setprecision(4);

    Outputfile << "Frames: " << frames << "\n";
    Outputfile << "Frame Time: " << frametime << "\n";


    for(int i =0; i<fr_set.size(); i++ )
    {
        for( int j = 0; j < fr_set[i].size(); j++ )
        {
            Outputfile << fr_set[i][j] << " ";
        }

        Outputfile << "\n";

    }


}


