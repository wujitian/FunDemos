/*
 * This example comes from 《OpenGL编程精粹》5.4 
 * Created Time: 2020-07-15 16:24:53
 * Last modified: 
 * @author: fabiokong@zhaoxin.com 
 */

#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>

void init();
void display();
void update(int value);

static float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
static float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static float lightPosition[] = { 0.0f, 0.0f, 5.0f, 1.0f };

static float diffuseLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float specularLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float lightPositionR[] = { 0.0f, 0.0f, 5.0f, 1.0f };

static float no_mat[] = {0.0, 0.0, 0.0, 1.0};
static float mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
static float mat_diffuse[] = {0.2, 0.5, 0.8, 1.0};
static float mat_specular[] = {1.0, 1.0, 1.0, 1.0};
static float no_shininess[] = {0.0};
static float low_shininess[] = {5.0};
static float high_shininess[] = {100.0};
static float mat_emission[] = {0.3, 0.2, 0.3, 0.0};

    
float m_bRedX = 20.0f;
float m_Angle = 20.0f;

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    
    glutCreateWindow("OpenGL 3D View");
    
    init();
    glutDisplayFunc(display);
    glutTimerFunc(500, update, 1);
    
    glutMainLoop();
    return 0;
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 5, 15);
    //glOrtho(-10, 10, -10, 10, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightR);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightR);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
        
    glTranslatef(0.0f, 0.0f, -10.0f);

    glPushMatrix();
        glRotatef(m_bRedX, 1.0f, 1.0f, 0.0f);

        glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);
        glTranslatef(lightPositionR[0], lightPositionR[1], lightPositionR[2]);
        
        glColor3f(1.0f, 0.0f, 0.0f);

        glPushAttrib(GL_LIGHTING_BIT);
            glDisable(GL_LIGHTING); 
            glutSolidSphere(0.1, 10, 10);
            glEnable(GL_LIGHTING);
        glPopAttrib();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-3.0f, 0.0f, 0.0f);

        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

        glRotatef(m_Angle, 1.0f, 1.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glutSolidCube(2.2);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(3.0f, 0.0f, 0.0f);

        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

        glRotatef(m_Angle, 1.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glutSolidTorus(0.8, 1.2, 5, 10);
    glPopMatrix();
    
    glFlush();
}

void update(int value)
{
    m_bRedX += 5.0f;
    m_Angle += 5.0f;
    glutPostRedisplay();
    glutTimerFunc(1000, update, value);
}



