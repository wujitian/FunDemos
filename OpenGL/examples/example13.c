/*
 * This example comes from 《OpenGL编程精粹》12.5 
 * Created Time: 2020-07-15 16:24:53
 * Last modified: 
 * @author: fabiokong@zhaoxin.com 
 */

#include <GL/glut.h>
#include <math.h>

void init();
void display();
void DrawSphere(float x, float y, float z);

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
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

    GLfloat lightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPosition[] = {0.0f, 0.0f, 0.0f, 1.0f};

    GLfloat mat_ambient[] = {0.0, 0.0, 0.8, 1.0};
    GLfloat mat_diffuse[] = {0.0, 0.3, 0.6, 1.0};
    GLfloat mat_specular[] = {1.0, 0.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {10.0};

    GLuint fogMode[] = {GL_LINEAR, GL_EXP, GL_EXP2};
    GLuint fogFilter = 2;
    GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};
    
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);

    glEnable(GL_FOG);
    {
        glFogi(GL_FOG_MODE, fogMode[fogFilter]);
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.2f);
        glFogf(GL_FOG_START, 1.0f);
        glFogf(GL_FOG_END, 10.0f);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float z_axis = -6.0f;

    for (int i = 1; i < 12; i++)
        DrawSphere(-3+i*0.8, 0.0, z_axis-i+1);

    glFlush();
}

void DrawSphere(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();
}



