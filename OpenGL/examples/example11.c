/*
 * This example comes from 《OpenGL编程精粹》9.4 
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

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -10.0f);
        glRotatef(30.0f, 1.0f, 1.0f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);

        glBegin(GL_QUADS);
            float r = 2.0f;
            
            // front
            glNormal3f(0.0f, 0.0f, 1.0f);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-r, -r, r);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(r, -r, r);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(r, r, r);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-r, r, r);
            
            // back
            glNormal3f(0.0f, 0.0f, -1.0f);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-r, -r, -r);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-r, r, -r);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(r, r, -r);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(r, -r, -r);
            
            // top
            glNormal3f(0.0f, 1.0f, 0.0f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-r, r, -r);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-r, r, r);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(r, r, r);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(r, r, -r);
            
            // bottom
            glNormal3f(0.0f, -1.0f, 0.0f);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-r, -r, -r);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(r, -r, -r);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(r, -r, r);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-r, -r, r);
            
            // right
            glNormal3f(1.0f, 0.0f, 0.0f);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(r, -r, -r);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(r, r, -r);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(r, r, r);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(r, -r, r);

            // left
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-r, -r, -r);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-r, -r, r);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-r, r, r);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-r, r, -r);

        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -10.0f);
        //glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        glBegin(GL_QUADS);
            float t = 3.0f;
            
            // front
            glNormal3f(0.0f, 0.0f, 1.0f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-t, -t, t);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(t, -t, t);
            glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(t, t, t);
            glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(-t, t, t);
        glEnd();

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
    glPopMatrix();
    
    glFlush();
}



