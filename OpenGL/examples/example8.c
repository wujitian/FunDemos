/*
 * This example comes from 《OpenGL编程精粹》6.6 
 * Created Time: 2020-07-15 16:24:53
 * Last modified: 
 * @author: fabiokong@zhaoxin.com 
 */

#include <GL/glut.h>
#include <math.h>

void init();
void display();

GLuint m_Pyramid;

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    
    glutCreateWindow("OpenGL 3D View");
    
    init();
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

    m_Pyramid = glGenLists(1); 
    if (m_Pyramid != 0)
    {
        glNewList(m_Pyramid, GL_COMPILE);
            glBegin(GL_TRIANGLES);
                // front
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.0f, 0.0f);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(-1.0f, -1.0f, 1.0f);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(1.0f, -1.0f, 1.0f);
                
                // right
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.0f, 0.0f);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(1.0f, -1.0f, 1.0f);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(1.0f, -1.0f, -1.0f);
                
                // back
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.0f, 0.0f);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(1.0f, -1.0f, -1.0f);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(-1.0f, -1.0f, -1.0f);
                
                // left
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.0f, 0.0f);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(-1.0f, -1.0f, -1.0f);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(-1.0f, -1.0f, 1.0f);
            glEnd();

            glBegin(GL_QUADS);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(-1.0f, -1.0f, 1.0f);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(1.0f, -1.0f, 1.0f);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(1.0f, -1.0f, -1.0f);
                glColor3f(1.0f, 0.0f, 1.0f);
                glVertex3f(-1.0f, -1.0f, -1.0f);
            glEnd();
        glEndList();
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            glLoadIdentity();
            glTranslatef(-3.0f + 2.0 * x, -2.0 + 2.0 * y, -10.0f);
            glScalef(0.8f, 0.8f, 0.8f);
            glRotatef(20.0f, 1.0f, 1.0f, 1.0f);
            glCallList(m_Pyramid);
        }
    }

    glFlush();
}



