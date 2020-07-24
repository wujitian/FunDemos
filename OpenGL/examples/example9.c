/*
 * This example comes from 《OpenGL编程精粹》7.1.3 & 7.2.4 
 * Created Time: 2020-07-15 16:24:53
 * Last modified: 
 * @author: fabiokong@zhaoxin.com 
 */

#include <GL/glut.h>
#include <math.h>

void init();
void display();

static GLubyte O_Rasters[13] = {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3,
                                0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e};
static GLubyte P_Rasters[13] = {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0,
                                0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe};
static GLubyte E_Rasters[13] = {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0,
                                0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff};
static GLubyte N_Rasters[13] = {0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf,
                                0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3};
static GLubyte G_Rasters[13] = {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3,
                                0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e};
static GLubyte L_Rasters[13] = {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0,
                                0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0};

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
    glClearColor(0.0, 0.0, 0.0, 0.5);
    glClearDepth(1.0f);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-10, 10, -10, 10, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
   
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
        
    glTranslatef(-10.0f, -10.0f, -6.0f);

    glColor3f(1.0f, 0.0f, 1.0f);
    glRasterPos2i(0, 0);

    glBitmap(8, 13, 0.0, 0.0, 15.0, 0.0, O_Rasters);
    glBitmap(8, 13, 0.0, 0.0, 15.0, 0.0, P_Rasters);
    glBitmap(8, 13, 0.0, 0.0, 15.0, 0.0, E_Rasters);
    glBitmap(8, 13, 0.0, 0.0, 15.0, 0.0, N_Rasters);
    glBitmap(8, 13, 0.0, 0.0, 15.0, 0.0, G_Rasters);
    glBitmap(8, 13, 0.0, 0.0, 15.0, 0.0, L_Rasters);

    glBegin(GL_TRIANGLES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(2.0, 3.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(8.0, 3.0);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(5.0, 8.0);
    glEnd();

    for (int i = 0; i < 5; i++)
    {
        glRasterPos2i(i*2, 10+i);
        glCopyPixels(2.0f*30, 3.0f*30, 6*30, 5*30, GL_COLOR);
    }

    glFlush();
}



