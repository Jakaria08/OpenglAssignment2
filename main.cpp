#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "JointLoader.h"
#include "camera.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "MotionData.h"


using namespace std;

void keyInput(unsigned char, int, int);
int readFile(char* object);
void OutputFile();
void setup();
void resize(int, int);
void drawScene(void);
void draw_lines(JointLoader *j, double x, double y, double z);



JointLoader j(true);

MotionData mod;
camera cam;
Vector3f initialPosition(0.0, 0.0, -50.0);

GLuint id;


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


    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    //glutSpecialFunc(Arrowkeys);

    setup();
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
    case 'd':
        cam.xTransl(-1.0);
        break;
    case 'D':
        cam.xTransl(1.0);
        break;
    case 'c':
        cam.yTransl(-1.0);
        break;
    case 'C':
        cam.yTransl(1.0);
        break;
    case 'z':
        cam.zTransl(-1.0);
        break;
    case 'Z':
        cam.zTransl(1.0);
        break;
    case 't':
        cam.xRotate(-10.0);
        break;
    case 'T':
        cam.xRotate(10.0);
        break;
    case 'a':
        cam.yRotate(-10.0);
        break;
    case 'A':
        cam.yRotate(10.0);
        break;
    case 'l':
        cam.zRotate(-10.0);
        break;
    case 'L':
        cam.zRotate(10.0);
        break;
    }

     glutPostRedisplay();
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

    cout<<value<<"\n";

    file>>line;


    value = j.delUnnecessary(line);



    if ( value == "MOTION" )
    {
       int i = j.num_Channels();
       mod.total_frame_size = i;
       mod.loadMotion(file);
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
    Outputfile << fixed << setprecision(5);
    Outputfile << "HIERARCHY" << "\n";
    j.outp(Outputfile);
    Outputfile << "MOTION" << "\n";
    mod.OutputMotion(Outputfile);
    Outputfile.close();
    cout <<"Output File created !!";
}


void setup()
{
    cam.initialize(persp, -1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);


    id = glGenLists(1);

    glNewList(id,GL_COMPILE);

    draw_lines(&j, j.offsetX, j.offsetY, j.offsetZ);


    glEndList();
}

void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    cam.glVolume(); // camera view volume

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cam.glPosition(); // camera transformation

    glTranslatef(initialPosition[0],initialPosition[1],initialPosition[2]);

    glCallList(id);


    glutSwapBuffers();



}

void draw_lines(JointLoader *j, double x, double y, double z)
{


    vector<JointLoader *>::const_iterator it;

    for ( it = j->get_children().begin(); it != j->get_children().end() ; it++ )
    {

        glm::vec3 Joffset;

        Joffset.x= (*it)->offsetX;
        Joffset.y= (*it)->offsetY;
        Joffset.z= (*it)->offsetZ;

        Joffset.x+=x;
        Joffset.y+=y;
        Joffset.z+=z;


        if ( (*it)->has_children()  )
        {
            draw_lines(*it,Joffset.x,Joffset.y,Joffset.z);
        }


        glBegin(GL_LINES);
        glColor3f(1.0,1.0,1.0);
        glVertex3f(x,y,z);
        glVertex3f(Joffset.x,Joffset.y,Joffset.z);
        glEnd();



    }
}



