#include <iostream>
#include <GL/glut.h>
#include "models.h"
#include "utility.h"

#define W_WIDTH 800
#define W_HEIGHT W_WIDTH
#define VP_WIDTH W_WIDTH
#define VP_HEIGHT W_HEIGHT

#define ORTHO_SPACE 10.0

#define ROTATION_SPEED 4.0

#define BULB_HEIGHT 10.0f

struct vec2 {
    GLfloat x;
    GLfloat y;
};

void display();
void processKey(int keycode, int x, int y);

void init();
void initMatrix();
void initLight();

void drawScene();

vec2 v2Rotation;
GLfloat bulb_height = 0.0;

int main(int argc, char *argv[])
{
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);

    glutInit(&argc, argv);

    glutCreateWindow("Nuar");

    glutDisplayFunc(display);

    glutSpecialFunc(processKey);

    init();

    glutMainLoop();

    return 0;
}

void display()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, VP_WIDTH, VP_HEIGHT);
    initMatrix();
    drawScene();

    glViewport(W_WIDTH, 0, VP_WIDTH, VP_HEIGHT);
    initMatrix();
    glRotatef(90, 1, 0, 0);
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
    case GLUT_KEY_PAGE_UP:
        bulb_height += 0.1;
        break;
    case GLUT_KEY_PAGE_DOWN:
        bulb_height -= 0.1;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void init() {
    glClearColor(0.5, 0.5, 0.5, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    initTextures();
}

void initMatrix()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ORTHO_SPACE, ORTHO_SPACE, -ORTHO_SPACE, ORTHO_SPACE, -ORTHO_SPACE, ORTHO_SPACE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void initLight()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT0, GL_AMBIENT, new GLfloat[]{ 0.1, 0.1, 0.1, 1 });
    glLightfv(GL_LIGHT0, GL_DIFFUSE, new GLfloat[]{ 0.8, 0.8, 0.8, 1 });
    glLightfv(GL_LIGHT0, GL_POSITION, new GLfloat[]{ 0.0, BULB_HEIGHT + bulb_height, 0.0, 1.0 });
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, new GLfloat[]{ 0, -1, 0 });
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0);

    //draw flashlight
    glPushMatrix();
    glTranslatef(0, BULB_HEIGHT + bulb_height, 0);
    glScalef(0.3, 1, 0.3);
    glutSolidCube(1);
    glPopMatrix();

    glLightfv(GL_LIGHT1, GL_AMBIENT, new GLfloat[]{ 0.2, 0.2, 0.05, 1 });
    glLightfv(GL_LIGHT1, GL_DIFFUSE, new GLfloat[]{ 0.2, 0.2, 0.2, 1 });
    glLightfv(GL_LIGHT1, GL_POSITION, new GLfloat[]{ 0.0, 1.0, 0.0, 0.0 });
}

void drawScene()
{
    glPushMatrix();

    initLight();

    //glRotatef(35.264, 1, 0, 0);
    //glRotatef(-45, 0, 1, 0);

    glRotatef(v2Rotation.y, 0, 1, 0);
    glRotatef(v2Rotation.x, 1, 0, 0);
    
    glPushMatrix();
    glScalef(3, 3, 3);
    setNewspaperMaterial();
    useTexture("newspaper");
    //drawNewspaper();
    glPopMatrix();

    glPushMatrix();
    useTexture("newspaper");
    //drawCarpet();
    glPopMatrix();

    useTexture("newspaper");
    drawFloor();
    useTexture("none");

    glPopMatrix();
}
