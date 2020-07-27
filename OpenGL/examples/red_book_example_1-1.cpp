#include <iostream>
using namespace std;

//#include "vgl.h"
//#include "LoadShaders.h"

#include "glad.h"
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

void display()
{
}

int main(int argc, char* argv[])
{
    gladLoadGL();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow(argv[0]);
    
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

