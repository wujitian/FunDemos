#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(-0.2, 0);
    glVertex2f(-0.6, 0.3);
    glVertex2f(-0.1, 0.2);
    glVertex2f(0, 0.8);
    glVertex2f(0.1, 0.2);
    glVertex2f(0.6, 0.3);
    glVertex2f(0.2, 0);
    glVertex2f(0.4, -0.5);
    glVertex2f(0, -0.1);
    glVertex2f(-0.4, -0.5);
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

