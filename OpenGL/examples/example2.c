#include <GL/glut.h>

void display()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    glPointSize(100);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0f);
    float v[2] = {0.5f, -0.5f};
    //glVertex2f(0.5f, -0.5f);
    //glVertex2fv(&v[0]);
    glVertex2fv(v);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();

    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutCreateWindow("test");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

