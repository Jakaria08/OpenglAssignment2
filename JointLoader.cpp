#include "JointLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

bool JointLoader::load(ifstream& infile)
{

    //char next_str[100];
    string line1;
    string value1;

    // name of joint

    infile >> line1;
    value1 = delUnnecessary(line1);


    //cout<<value1<<"\n";

     this->name = value1;

     while (infile >> line1)
     {
        value1 = delUnnecessary(line1);

         if (value1 == "JOINT")
         {
             JointLoader child;
             child.is_root = false;
             child.load(infile);
             this->childjoints.push_back(child);
         }
         else if (value1 == "End")
         {
             JointLoader child(false,true);
             child.load(infile);
             this->childjoints.push_back(child);
         }
         else if ( value1 == "OFFSET")
         {
             double x,y,z;
             infile >> x >> y >> z;
             //cout<<x<<" "<<y<<" "<<z<<"\n";
             set_offset(x,y,z);
         }
         else if ( value1 == "CHANNELS")
         {

             read_channels(infile);

         }
         else if (value1 == "}")
             break;
     }


}


void JointLoader::read_channels(ifstream& infile)
{


    int num;
    string type,temp;
    infile >> num;
    cout<<num;


    for(int i = 0; i < num; i++ )
    {

        infile >> temp;

        type = delUnnecessary(temp);

        //cout << type;

        if(type == "Xposition") {

            channels.push_back(X_POSITION);
            }

        else if(type == "Yposition"){

            channels.push_back(Y_POSITION);
            }

        else if(type == "Zposition"){

            channels.push_back(Z_POSITION);
            }

        else if(type == "Xrotation"){

            channels.push_back(X_ROTATION);
            }

        else if(type == "Yrotation"){

            channels.push_back(Y_ROTATION);
            }

        else if(type == "Zrotation"){

            channels.push_back(Z_ROTATION);
            }

        else
        {
            fprintf(stderr,"Invalid channel! \n");
            exit(-1);
        }
    }
}


void JointLoader::print(ofstream& outfile, const char *offset )
{

    char next_offset[15] = "\t\0";

    strcat(next_offset,offset);

    if(is_root)
    {
        outfile << "ROOT " << this->name <<"\n";
    }
    else if(is_end)
    {
        outfile << offset << "End Site" << "\n";
        }
    else
    {
        outfile << offset << "JOINT "<< this->name << "\n";

    }

    outfile << offset << "{" << "\n";


    outfile << next_offset << "OFFSET "<< o.x <<" "<<o.y <<" "<<o.z << "\n";

    if ( channels.size() > 0 )
    {

        outfile << next_offset << "CHANNELS " << channels.size() <<" " ;

        vector<ChannelType>::iterator it;

        for(it=channels.begin(); it != channels.end(); it++ )
        {

            switch(*it)
            {

            case X_POSITION:
                outfile << "Xposition ";
                break;
            case Y_POSITION:
                outfile << "Yposition ";
                break;
            case Z_POSITION:
                outfile << "Zposition ";
                break;
            case X_ROTATION:
                outfile << "Xrotation ";
                break;
            case Y_ROTATION:
                outfile << "Yrotation ";
                break;
            case Z_ROTATION:
               outfile << "Zrotation ";
                break;
            }
        }
        outfile << "\n";

    }

    vector<JointLoader>::iterator itj;

    for(itj=childjoints.begin(); itj !=childjoints.end() ; itj++ )
    {
        itj->print(outfile,next_offset);
    }
    outfile << offset << "}" << "\n";

}
