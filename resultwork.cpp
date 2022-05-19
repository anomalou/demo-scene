#define _USE_MATH_DEFINES

#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include "models.h"
#include "utility.h"

#define W_WIDTH 800
#define W_HEIGHT W_WIDTH
#define VP_WIDTH W_WIDTH
#define VP_HEIGHT W_HEIGHT

#define PROJ_SPACE 10.0

#define ROTATION_SPEED 1.0

#define CAMERA_SPEED 1.0

struct vec2 {
    GLfloat x;
    GLfloat y;
};

struct vec3 {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

void display();
void processKey(int keycode, int x, int y);

void init();
void initMatrix();
void enableModes();
void enableLight();
void enableFlashlight();

void drawScene();

void moveCamera(GLfloat speed);
void rotateCamera(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

vec3 v3CamPos;
vec3 v3CamView;
vec3 v3CamUp;

GLfloat light_intense = 0.0;

bool enableLightning = true;
bool enableTextures = true;

bool enableLight0 = true;
bool enableFlashlight2 = false;

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

    enableModes();

    glViewport(0, 0, VP_WIDTH, VP_HEIGHT);
    initMatrix();
    drawScene();

    glViewport(W_WIDTH, 0, VP_WIDTH, VP_HEIGHT);
    glRotatef(90, 1, 0, 0);
    initMatrix();
    drawScene();

    glutSwapBuffers();
}

void processKey(int keycode, int x, int y)
{
    switch (keycode)
    {
    case GLUT_KEY_LEFT:
        rotateCamera(ROTATION_SPEED * 2.0, 0, 1, 0);
        break;
    case GLUT_KEY_RIGHT:
        rotateCamera(-ROTATION_SPEED * 2.0, 0, 1, 0);
        break;
    case GLUT_KEY_UP:
        moveCamera(CAMERA_SPEED);
        break;
    case GLUT_KEY_DOWN:
        moveCamera(-CAMERA_SPEED);
        break;
    case GLUT_KEY_HOME:
        v3CamPos.y += CAMERA_SPEED;
        v3CamView.y += CAMERA_SPEED;
        break;
    case GLUT_KEY_END:
        v3CamPos.y -= CAMERA_SPEED;
        v3CamView.y -= CAMERA_SPEED;
        break;
    case GLUT_KEY_PAGE_UP:
        if(light_intense < 1.0f)
            light_intense += 0.1;
        break;
    case GLUT_KEY_PAGE_DOWN:
        if(light_intense > 0.0f)
            light_intense -= 0.1;
        break;
    case GLUT_KEY_F1:
        enableLight0 = !enableLight0;
        break;
    case GLUT_KEY_F2:
        enableFlashlight2 = !enableFlashlight2;
        break;
    case GLUT_KEY_F3:
        enableLightning = !enableLightning;
        break;
    case GLUT_KEY_F4:
        enableTextures = !enableTextures;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LIGHTING);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    initTextures();

    v3CamPos = { 0.0, 0.0, 0.0 };
    v3CamView = { 0.0, 0.0, -1.0 };
    v3CamUp = { 0.0, 1.0, 0.0 };
}

void initMatrix()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-PROJ_SPACE, PROJ_SPACE, -PROJ_SPACE, PROJ_SPACE, PROJ_SPACE, PROJ_SPACE * 6);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(v3CamPos.x, v3CamPos.y, v3CamPos.z,
              v3CamView.x, v3CamView.y, v3CamView.z,
              v3CamUp.x, v3CamUp.y, v3CamUp.z);
}

void enableModes() {
    if (enableLightning)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);

    if (enableTextures)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
}

void enableLight()
{
    if (enableLight0)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT0, GL_AMBIENT, new GLfloat[]{ 0.1, 0.1, 0.1, 1 });
    glLightfv(GL_LIGHT0, GL_DIFFUSE, new GLfloat[]{ 0.8, 0.8, 0.8, 1 });
    glLightfv(GL_LIGHT0, GL_POSITION, new GLfloat[]{ 0.0, BULB_HEIGHT, 0.0, 1.0 });
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, new GLfloat[]{ 0, -1, 0 });
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 40.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 15.0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, new GLfloat[]{ 0.2, 0.2, 0.2, 1 });
    glLightfv(GL_LIGHT1, GL_DIFFUSE, new GLfloat[]{ light_intense, light_intense, light_intense, 1 });
    glLightfv(GL_LIGHT1, GL_POSITION, new GLfloat[]{ 1.0, 1.0, 1.0, 0.0 });
}

void enableFlashlight() {
    if (enableFlashlight2)
        glEnable(GL_LIGHT2);
    else
        glDisable(GL_LIGHT2);

    glLightfv(GL_LIGHT2, GL_AMBIENT, new GLfloat[]{ 0.1, 0.1, 0.1, 1.0 });
    glLightfv(GL_LIGHT2, GL_DIFFUSE, new GLfloat[]{ 0.8, 0.8, 0.8, 1.0 });
    glLightfv(GL_LIGHT2, GL_SPECULAR, new GLfloat[]{ 1.0, 1.0, 1.0, 1.0 });
    glLightfv(GL_LIGHT2, GL_POSITION, new GLfloat[]{ 0.0, 0.0, 5.0, 1.0 });
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, new GLfloat[]{ 0, 0, -1 });
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);
}

void drawScene()
{
    glPushMatrix();

    enableFlashlight();
    glTranslatef(0, -5, -PROJ_SPACE * 2);

    enableLight();

    glPushMatrix();
    glTranslatef(0, BULB_HEIGHT, 0);
    drawLamp(enableLight0);
    glPopMatrix();
    
    glPushMatrix();
    setTableMaterial();
    useTexture("table");
    drawTable();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(-1.0, 0, TABLE_HEIGHT + TABLE_LEG_WIDTH);
    glRotatef(30, 0, 0, 1);
    glScalef(2, 2, 2);
    setNewspaperMaterial();
    useTexture("newspaper");
    drawNewspaper();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0, BALL_SCALE / 2.0 + TABLE_HEIGHT + TABLE_LEG_WIDTH, 0);
    setBallMaterial();
    drawBall();
    glPopMatrix();

    setWallMaterial();
    glPushMatrix();
    useTexture("wall");
    drawWalls();
    glPopMatrix();

    setFloorMaterial();
    glPushMatrix();
    useTexture("floor");
    drawFloor();
    glPopMatrix();


    setCarpetMaterial();
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(30, 0, 0, 1);
    glTranslatef(0, 0, 0.1);
    useTexture("carpet");
    glEnable(GL_BLEND);
    drawCarpet();
    disableEmission();
    glDisable(GL_BLEND);
    glPopMatrix();

    useTexture("none");

    glPopMatrix();
}

void moveCamera(GLfloat speed) {
    vec3 v = { 0 };

    v.x = v3CamView.x - v3CamPos.x;
    v.y = v3CamView.y - v3CamPos.y;
    v.z = v3CamView.z - v3CamPos.z;

    v3CamPos.x += v.x * speed;
    v3CamPos.z += v.z * speed;
    v3CamView.x += v.x * speed;
    v3CamView.z += v.z * speed;
}

void rotateCamera(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    vec3 newView = { 0 };
    vec3 v = { 0 };

    v.x = v3CamView.x - v3CamPos.x;
    v.y = v3CamView.y - v3CamPos.y;
    v.z = v3CamView.z - v3CamPos.z;

    GLfloat rangle = angle * M_PI / 180.0f;

    GLfloat cosTheta = (GLfloat)cos(rangle);
    GLfloat sinTheta = (GLfloat)sin(rangle);

    newView.x = (cosTheta + (1 - cosTheta) * x * x) * v.x;
    newView.x += ((1 - cosTheta) * x * y - z * sinTheta) * v.y;
    newView.x += ((1 - cosTheta) * x * z + y * sinTheta) * v.z;

    newView.y = ((1 - cosTheta) * x * y + z * sinTheta) * v.x;
    newView.y += (cosTheta + (1 - cosTheta) * y * y) * v.y;
    newView.y += ((1 - cosTheta) * y * z - x * sinTheta) * v.z;

    newView.z = ((1 - cosTheta) * x * z - y * sinTheta) * v.x;
    newView.z += ((1 - cosTheta) * y * z + x * sinTheta) * v.y;
    newView.z += (cosTheta + (1 - cosTheta) * z * z) * v.z;

    v3CamView.x = v3CamPos.x + newView.x;
    v3CamView.y = v3CamPos.y + newView.y;
    v3CamView.z = v3CamPos.z + newView.z;
}
