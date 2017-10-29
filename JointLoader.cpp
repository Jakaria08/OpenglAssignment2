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


    string line1;
    string value1;

//name of joint
    infile >> line1;
    value1 = delUnnecessary(line1);


    //cout<<value1<<"\n";


     this->name = value1;

     while (infile >> line1)
     {
        value1 = delUnnecessary(line1);

         if (value1 == "JOINT")
         {
             JointLoader *childJoint = new JointLoader(false,false,this);
             childJoint->load(infile);
             this->childjoints.push_back(childJoint);
         }
         else if (value1 == "End")
         {
             JointLoader *childJoint = new JointLoader(false,true,this);
             childJoint->load(infile);
             this->childjoints.push_back(childJoint);
         }
         else if ( value1 == "OFFSET")
         {
             double x,y,z;
             infile >> x >> y >> z;
             //cout<<x<<" "<<y<<" "<<z<<"\n";
             this->offsetX = x;
             this->offsetY = y;
             this->offsetZ = z;
         }
         else if ( value1 == "CHANNELS")
         {

             Channels(infile);

         }
         else if (value1 == "}")
             break;
     }


}


void JointLoader::Channels(ifstream& infile)
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


void JointLoader::outp(ofstream& outfile, const char *offset )
{

    char spacing[20] = "\t\0";

    strcat(spacing,offset);

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


    outfile << spacing << "OFFSET "<< this->offsetX <<" "<<this->offsetY <<" "<<this->offsetZ << "\n";

    if ( channels.size() > 0 )
    {

        outfile << spacing << "CHANNELS " << channels.size() <<" " ;

        //vector<int>::iterator it;

        for(int i=0; i<channels.size(); i++ )
        {

            switch(channels[i])
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

    for(int i = 0; i<childjoints.size(); i++)
    {
        childjoints[i]->outp(outfile,spacing);
    }
    outfile << offset << "}" << "\n";

}
