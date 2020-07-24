/*
 * This example comes from 《OpenGL编程精粹》11.2 & 11.3 
 * Created Time: 2020-07-15 16:24:53
 * Last modified: 
 * @author: fabiokong@zhaoxin.com 
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

int listBase;

void init();
void display();
void init_for_polygon();
void display_for_polygon();

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    
    glutCreateWindow("OpenGL 3D View");
    
    //init();
    //glutDisplayFunc(display);
    
    init_for_polygon();
    glutDisplayFunc(display_for_polygon);
    
    glutMainLoop();
    return 0;
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

    glClearColor(0.0, 0.0, 0.0, 0.5);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(2.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -7.0f);
    glRotatef(30.0f, 1.0f, 1.0f, 0.0f);
    glutWireCube(1.5);

    glFlush();
}

void init_for_polygon()
{
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

    glClearColor(0.0, 0.0, 0.0, 0.5);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glLineWidth(2.0);
}

void display_for_polygon()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -7.0f);
        glRotatef(30.0f, 1.0f, 0.0f, 1.0f);
        glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
        glBegin(GL_TRIANGLES);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -7.0f);
        glRotatef(-30.0f, 1.0f, 0.0f, 1.0f);
        glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
        glBegin(GL_TRIANGLES);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
        glEnd();
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);

    glFlush();
}



