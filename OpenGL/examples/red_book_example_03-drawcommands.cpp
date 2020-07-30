#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "vgl.h"
#include "vapp.h"

#include "LoadShaders.h"

BEGIN_APP_DECLARATION(DrawCommandExample)
    // Override functions from base class
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Resize(int width, int height);

    // Member variables
    float aspect;
    GLuint render_prog;
    GLuint vao[1];
    GLuint vbo[1];
    GLuint ebo[1];

    GLint render_model_matrix_loc;
    GLint render_projection_matrix_loc;
END_APP_DECLARATION()

//DEFINE_APP(DrawCommandExample, "Drawing Commands Example")

void init(void)
{
}

void display(void)
{
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow(argv[0]);

    glewExperimental = GL_TRUE;
    if (glewInit())
    {
        cerr << "Unable to initialze GLEW ... exiting" << endl;
        exit(EXIT_FAILURE);
    }
    
    init();
    
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}

