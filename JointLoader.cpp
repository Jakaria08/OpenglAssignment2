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
             JointLoader childJoint;
             childJoint.load(infile);
             this->childjoints.push_back(childJoint);
         }
         else if (value1 == "End")
         {
             JointLoader childJoint(false,true);
             childJoint.load(infile);
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

            channels1.push_back(X_POSITION1);
            }

        else if(type == "Yposition"){

            channels1.push_back(Y_POSITION1);

            }

        else if(type == "Zposition"){

            channels1.push_back(Z_POSITION1);
            }

        else if(type == "Xrotation"){

            channels1.push_back(X_ROTATION1);
            }

        else if(type == "Yrotation"){

            channels1.push_back(Y_ROTATION1);
            }

        else if(type == "Zrotation"){

            channels1.push_back(Z_ROTATION1);
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

    if ( channels1.size() > 0 )
    {

        outfile << spacing << "CHANNELS " << channels1.size() <<" " ;

        //vector<int>::iterator it;

        for(int i=0; i<channels1.size(); i++ )
        {

            switch(channels1[i])
            {

            case X_POSITION1:
                outfile << "Xposition ";
                break;
            case Y_POSITION1:
                outfile << "Yposition ";
                break;
            case Z_POSITION1:
                outfile << "Zposition ";
                break;
            case X_ROTATION1:
                outfile << "Xrotation ";
                break;
            case Y_ROTATION1:
                outfile << "Yrotation ";
                break;
            case Z_ROTATION1:
               outfile << "Zrotation ";
                break;
            }
        }
        outfile << "\n";

    }

    for(int i = 0; i<childjoints.size(); i++)
    {
        childjoints[i].outp(outfile,spacing);
    }
    outfile << offset << "}" << "\n";

}
