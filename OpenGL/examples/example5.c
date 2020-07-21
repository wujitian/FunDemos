/*
 * This example comes from 《OpenGL编程精粹》3.5 
 * Created Time: 2020-07-15 16:24:53
 * Last modified: 
 * @author: fabiokong@zhaoxin.com 
 */

#include <GL/glut.h>
#include <math.h>

void init();
void display();

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
}

//void display()
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//        
//    glColor3f(1.0, 0, 0);
//    glutWireTeapot(3);
//    
//    glFlush();
//}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
        glTranslatef(-1.5f, 1.0f, -6.0f);
        glScalef(0.75f, 0.75f, 0.75f);
        //glRotatef(90.0f, 1.0f, 1.0f, 1.0f);
        glColor3f(1.0f, 0.0f, 0.0f);

        glBegin(GL_LINE_LOOP);
            glVertex3f(0.0f, 1.0f, -0.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
        glEnd();
    glPopMatrix();
    
    
    glPushMatrix();
        glTranslatef(1.5f, 1.0f, -6.0f);
        glScalef(0.75f, 0.75f, 0.75f);
        //glRotatef(30.0f, 1.0f, 1.0f, 1.0f);
        glColor3f(1.0f, 0.0f, 1.0f);

        glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i <= 370; i+=10)
            {
                float p = (float)(i * 3.14 / 180);
                glVertex3f((float)sin(p), (float)cos(p), 0.0f);   // add "-lm" to CMakeList.txt
            }
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-1.5f, -1.0f, -6.0f);
        glScalef(0.75f, 0.75f, 0.75f);
        //glRotatef(30.0f, 1.0f, 1.0f, 1.0f);
        glColor3f(0.0f, 1.0f, 1.0f);

        glBegin(GL_TRIANGLES);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(1.5f, -1.0f, -6.0f);
        glScalef(0.75f, 0.75f, 0.75f);
        //glRotatef(30.0f, 1.0f, 1.0f, 1.0f);
        glColor3f(1.0f, 1.0f, 0.0f);

        glBegin(GL_QUADS);
            glVertex3f(-1.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
        glEnd();
    glPopMatrix();

    glFlush();
}



