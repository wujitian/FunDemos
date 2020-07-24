/*
 * This example comes from 《OpenGL编程精粹》13.7 
 * Created Time: 2020-07-15 16:24:53
 * Last modified: 
 * @author: fabiokong@zhaoxin.com 
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
    
GLuint list;

void init();
void display();

void beginCallback(GLenum which)
{
    glBegin(which);
}

void errorCallback(GLenum errorCode)
{
    const GLubyte * string;
    string = gluErrorString(errorCode);
    printf("Tessellation Error: %s\n", string);
    exit(0);
}

void endCallback(void)
{
    glEnd();
}

void vertexCallback(GLvoid * vertex)
{
    GLdouble * pt;
    GLubyte red, green, blue;
    pt = (GLdouble *)vertex;
    red = (GLubyte)rand() & 0xff;
    green = (GLubyte)rand() & 0xff;
    blue = (GLubyte)rand() & 0xff;
    glColor3ub(red, green, blue);
    glVertex3dv(pt);
}

void combineCallback(GLdouble coords[3], GLdouble * vertex_data[4], GLfloat weight[4], GLdouble ** dataout)
{
    GLdouble *vertex;
    int i;
    vertex = (GLdouble *)malloc(6*sizeof(GLdouble));

    vertex[0] = coords[0];
    vertex[1] = coords[1];
    vertex[2] = coords[2];

    for (i = 3; i < 6; ++i)
    {
        vertex[i] = weight[0] * vertex_data[0][i] + weight[1] * vertex_data[1][i] + 
                    weight[2] * vertex_data[2][i] + weight[3] * vertex_data[3][i];
    }
    *dataout = vertex;
}

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
    glOrtho(-10, 10, -10, 10, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

    
    GLUtesselator *tobj;

    GLuint polygonMode[] = {GL_FILL, GL_LINE};
    GLuint polyMode = 1;

    GLdouble TessProperty[5] = 
    {
        GLU_TESS_WINDING_ODD,
        GLU_TESS_WINDING_NONZERO,
        GLU_TESS_WINDING_POSITIVE,
        GLU_TESS_WINDING_NEGATIVE,
        GLU_TESS_WINDING_ABS_GEQ_TWO
    };
    GLuint nProperty = 1;

    GLdouble rectOut[4][3] = {-5.0, -5.0, 0.0, 
                               5.0, -5.0, 0.0,
                               5.0, 5.0, 0.0,
                              -5.0, 5.0, 0.0};
    GLdouble rectIn[4][3] = {-2.0, -2.0, 0.0,
                              2.0, -2.0, 0.0,
                              2.0, 2.0, 0.0,
                             -2.0, 2.0, 0.0};
    GLdouble star[6][3] = {-5.1, -3.0, 0.0, 5.1, -3.0, 0.0, 0.0, 6.0, 0.0,
                            0.0, -6.0, 0.0, 5.1, 3.0, 0.0, -5.1, 3.0, 0.0};

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode[polyMode]);

    list = glGenLists(2);
    tobj = gluNewTess();
    gluTessCallback(tobj, GLU_TESS_VERTEX, glVertex3dv);
    //gluTessCallback(tobj, GLU_TESS_VERTEX, vertexCallback);
    gluTessCallback(tobj, GLU_TESS_BEGIN, beginCallback);
    gluTessCallback(tobj, GLU_TESS_END, endCallback);
    gluTessCallback(tobj, GLU_TESS_ERROR, errorCallback);
    gluTessCallback(tobj, GLU_TESS_COMBINE, combineCallback);

    glNewList(list, GL_COMPILE);
    gluTessProperty(tobj, GLU_TESS_WINDING_RULE, TessProperty[nProperty]);

    gluTessBeginPolygon(tobj, NULL);
        gluTessBeginContour(tobj);
            gluTessVertex(tobj, rectOut[0], rectOut[0]);
            gluTessVertex(tobj, rectOut[1], rectOut[1]);
            gluTessVertex(tobj, rectOut[2], rectOut[2]);
            gluTessVertex(tobj, rectOut[3], rectOut[3]);
        gluTessEndContour(tobj);
        
        gluTessBeginContour(tobj);
            gluTessVertex(tobj, rectIn[0], rectIn[0]);
            gluTessVertex(tobj, rectIn[1], rectIn[1]);
            gluTessVertex(tobj, rectIn[2], rectIn[2]);
            gluTessVertex(tobj, rectIn[3], rectIn[3]);
        gluTessEndContour(tobj);
    gluTessEndPolygon(tobj);
    glEndList();
    
    
    glNewList(list+1, GL_COMPILE);
    gluTessProperty(tobj, GLU_TESS_WINDING_RULE, TessProperty[nProperty]);
    gluTessBeginPolygon(tobj, NULL);
        gluTessBeginContour(tobj);
            gluTessVertex(tobj, star[0], star[0]);
            gluTessVertex(tobj, star[1], star[1]);
            gluTessVertex(tobj, star[2], star[2]);
        gluTessEndContour(tobj);
        
        gluTessBeginContour(tobj);
            gluTessVertex(tobj, star[3], star[3]);
            gluTessVertex(tobj, star[4], star[4]);
            gluTessVertex(tobj, star[5], star[5]);
        gluTessEndContour(tobj);
    gluTessEndPolygon(tobj);
    glEndList();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
        glTranslatef(-4.0f, 1.0f, -6.0f);
        glScalef(0.6f, 0.6f, 0.6f);
        //glRotatef(30.0f, 1.0f, 1.0f, 1.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glCallList(list);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(4.0f, 1.0f, -6.0f);
        glScalef(0.6f, 0.6f, 0.6f);
        //glRotatef(30.0f, 1.0f, 1.0f, 1.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glCallList(list+1);
    glPopMatrix();
    
    glFlush();
}



