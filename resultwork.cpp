// resultwork.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <GL/freeglut.h>

#define W_WIDTH 800
#define W_HEIGHT W_WIDTH
#define VP_WIDTH W_WIDTH
#define VP_HEIGHT W_HEIGHT

#define ORTHO_SPACE 5.0

#define ROTATION_SPEED 4.0

struct vec2 {
    GLfloat x;
    GLfloat y;
};

void display();
void processKey(int keycode, int x, int y);

void initMatrix();
void initLight();
void initMaterial();

void drawScene();

vec2 v2Rotation;

int main(int argc, char *argv[])
{
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);

    glutInit(&argc, argv);

    glutCreateWindow("Nuar");

    glutDisplayFunc(display);

    glutSpecialFunc(processKey);

    glutMainLoop();

    return 0;
}

void display()
{
    glClearColor(0.5, 0.5, 0.5, 1);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, VP_WIDTH, VP_HEIGHT);

    initMatrix();
    initLight();

    drawScene();

    glutSwapBuffers();
}

void processKey(int keycode, int x, int y)
{
    switch (keycode)
    {
    case GLUT_KEY_LEFT:
        v2Rotation.y -= ROTATION_SPEED;
        break;
    case GLUT_KEY_RIGHT:
        v2Rotation.y += ROTATION_SPEED;
        break;
    case GLUT_KEY_UP:
        v2Rotation.x -= ROTATION_SPEED;
        break;
    case GLUT_KEY_DOWN:
        v2Rotation.x += ROTATION_SPEED;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void initMatrix()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ORTHO_SPACE, ORTHO_SPACE, ORTHO_SPACE, -ORTHO_SPACE, ORTHO_SPACE, -ORTHO_SPACE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void initLight()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, new GLfloat[]{ 0.99, 0.9, 0.05, 1 });
    glLightfv(GL_LIGHT0, GL_POSITION, new GLfloat[]{ 0.0, -1.0, 0.0, 0.0 });
}

void drawScene()
{
    glPushMatrix();

    glRotatef(v2Rotation.y, 0, 1, 0);
    glRotatef(v2Rotation.x, 1, 0, 0);
    glutSolidTeacup(3.0);

    glPopMatrix();
}
