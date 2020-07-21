/*
 * This example comes from 《OpenGL编程精粹》4.5 
 * Created Time: 2020-07-15 16:24:53
 * Last modified: 
 * @author: fabiokong@zhaoxin.com 
 */

#include <GL/glut.h>
#include <math.h>

#define GL_PI 3.1415926 

void init();
void display();

static GLfloat vertices[] = {1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 
                            -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
                            -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f};

static GLfloat colors[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                           0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                           1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                           0.4f, 0.6f, 0.3f, 0.0f, 0.8f, 0.4f};

static GLbyte indexs[] = {0, 1, 2, 3,
                          4, 5, 6, 7,
                          0, 3, 4, 7,
                          2, 5, 4, 3,
                          2, 1, 6, 5,
                          0, 1, 6, 7};

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

    glEnable(GL_VERTEX_ARRAY);
    glEnable(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
        glTranslatef(-1.5f, 0.5f, -7.0f);
        glRotatef(20.0f, 1.0f, 1.0f, 0.0f);
        glShadeModel(GL_FLAT);

        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f, 1.8f, 0.0f);
            int m_Pivot = 0;
            for (float angle = 0.0f; angle < 2.0f * GL_PI; angle += GL_PI/8.0f)
            {
                if (m_Pivot % 2 == 0)
                {
                    glColor3f(0.0f, 1.0f, 0.0f);
                }
                else
                {
                    glColor3f(0.0f, 0.0f, 1.0f);
                }

                m_Pivot++;
                glVertex3f(0.8 * sin(angle), 0.0f, 0.8*cos(angle));
            }
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0.0f, 0.0f);
            for (float angle = 0.0f; angle < 2.0f * GL_PI; angle += GL_PI/8.0f)
            {
                if (m_Pivot % 2 == 0)
                {
                    glColor3f(0.0f, 1.0f, 0.0f);
                }
                else
                {
                    glColor3f(0.0f, 0.0f, 1.0f);
                }
                m_Pivot++;
                glVertex3f(0.8 * sin(angle), 0.0f, 0.8*cos(angle));
            }
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(1.5f, 1.0f, -7.0f);
        glRotatef(60.0f, 1.0f, 1.0f, 1.0f);
        glScalef(0.75f, 0.75f, 0.75f);
        glShadeModel(GL_SMOOTH);
        glBegin(GL_QUADS);
            for (int i = 0; i < 6; ++i)
            {
                glArrayElement(indexs[4*i]);
                glArrayElement(indexs[4*i + 1]);
                glArrayElement(indexs[4*i + 2]);
                glArrayElement(indexs[4*i + 3]);
            }
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-1.5f, -1.5f, -7.0f);
        glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
        glColor3f(0.3f, 0.7f, 0.6f);
        glutWireSphere(1.0, 50, 50);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(1.5f, -1.5f, -7.0f);
        glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
        glColor3f(0.3f, 0.6f, 0.2f);
        glutWireTeapot(1.0);
    glPopMatrix();


    glFlush();
}



