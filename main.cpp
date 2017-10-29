#include <GL/glew.h>
#include <GL/freeglut.h>
//#include <glm/glm.hpp>
#include "JointLoader.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

void keyInput(unsigned char, int, int);
int readFile(char* object);
void OutputFile();

JointLoader j = new JointLoader();


int main(int argc, char *argv[])
{
    //INIT GLUT PROCEDURES


    if(argv[1]==NULL)
    {
        printf("\n\nPlease Specify Object File!\n\n");
    }
    else
    {
        readFile(argv[1]);
    }

    glutInit(&argc, argv);
    glutInitContextVersion(2, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("MotionViewer");



    //glutDisplayFunc(drawScene);
    //glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    //glutSpecialFunc(Arrowkeys);


    glutMainLoop();

    return 0;
}




void keyInput(unsigned char key, int x, int y)
{

    switch(key)
    {
    case 'w':
        OutputFile();
        break;
    case 'q':
        exit(1);
        break;
    }
}


int readFile(char* object)
{

    string line;
    string value;


    stringstream ss;
    ss << "a2files//" << object;
    string path = ss.str();

    ifstream file;

    file.open(path.c_str());

    if (file.is_open())
    {
        cout << "\n\nFile successfully opened !! \n\n";

    }
    else
    {
        cout << "\n\nError opening file \n\n";
    }

    cout << "\n\nFile reading started..........\n\n";

    file>>line;

    value = j.delUnnecessary(line);


    if (value == "HIERARCHY")
    {

        //cout<<value<<"\n";


        file>>line;

        value = j.delUnnecessary(line);

        //cout<<value<<"\n";

        if ( value == "ROOT" )
        {
            j.load(file);
        }
        else
        {
            cout<< "Root needed \n";
        }


    }
    else if ( value == "MOTION" )
    {
        printf(" baki ache");
    }
    else
    {
        cout<<"Error.\n";
        return -1;
    }

    file.close();

    cout<<"File Loaded !!!";

    return 0;

}

void OutputFile()
{
    cout<<"Creating Output File.....................";
    ofstream Outputfile;
    Outputfile.open("output.bvh");
    Outputfile << "HIERARCHY" << "\n";
    j.outp(Outputfile);
    Outputfile.close();
    cout <<"Output File created !!";
}
