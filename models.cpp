#include <GL/glut.h>
#include "models.h"

void setCarpetMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, new GLfloat[]{ 0.2, 0.2, 1.0, 1.0 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[]{ 0.5, 0.5, 0.5, 1.0 });
	glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[]{ 1.0, 1.0, 1.0, 1.0 });
	glMaterialfv(GL_FRONT, GL_EMISSION, new GLfloat[]{ 0.0, 0.0, 0.8, 1.0 });
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
}

void setFloorMaterial() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, new GLfloat[]{ 0.0, 0.0, 0.0, 1.0 });
	glMaterialfv(GL_FRONT, GL_DIFFUSE, new GLfloat[]{ 0.8, 0.8, 0.8, 1.0 });
	glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[]{ 1.0, 1.0, 1.0, 1.0 });
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);
}

void setWallMaterial() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, new GLfloat[]{ 0.0, 0.0, 0.0, 1.0 });
	glMaterialfv(GL_FRONT, GL_DIFFUSE, new GLfloat[]{ 0.5, 0.5, 0.5, 1.0 });
	glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[]{ 1.0, 1.0, 1.0, 1.0 });
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);
}

void setTableMaterial() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, new GLfloat[]{ 0.0, 0.0, 0.0, 1.0 });
	glMaterialfv(GL_FRONT, GL_DIFFUSE, new GLfloat[]{ 0.8, 0.8, 0.8, 1.0 });
	glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[]{ 1.0, 1.0, 1.0, 1.0 });
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);
}

void setNewspaperMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, new GLfloat[]{ 0.1, 0.1, 0.1, 1.0 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[]{ 0.6, 0.6, 0.6, 1.0 });
	glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[]{ 1.0, 1.0, 1.0, 1.0 });
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
}

void setLampMaterial() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, new GLfloat[]{ 0.4, 0.4, 0.4, 1.0 });
	glMaterialfv(GL_FRONT, GL_DIFFUSE, new GLfloat[]{ 0.8, 0.8, 0.8, 1.0 });
	glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[]{ 1.0, 1.0, 1.0, 1.0 });
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
}

void setBallMaterial() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, new GLfloat[]{ 0.1, 0.1, 0.1, 1.0 });
	glMaterialfv(GL_FRONT, GL_DIFFUSE, new GLfloat[]{ 0.7, 0.1, 0.1, 1.0 });
	glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[]{ 1.0, 1.0, 1.0, 1.0 });
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
}

void enableEmission() {
	glMaterialfv(GL_FRONT, GL_EMISSION, new GLfloat[]{ 0.8, 0.8, 0.8, 1.0 });
}

void disableEmission() {
	glMaterialfv(GL_FRONT, GL_EMISSION, new GLfloat[]{ 0.0, 0.0, 0.0, 1.0 });
}

void drawPlate(int width, int height, int tex_s, int tex_t) {
	GLfloat tile_w = 1.0f / (GLfloat)width;
	GLfloat tile_h = 1.0f / (GLfloat)height;

	if (tex_s == 0)
		tex_s = width;
	GLfloat ftex_s = 1.0f / (GLfloat)tex_s;
	if (tex_t == 0)
		tex_t = height;
	GLfloat ftex_t = 1.0f / (GLfloat)tex_t;

	int x_count = 0;
	int y_count = 0;

	for (GLfloat x = -0.5; x < 0.5; x += tile_w, x_count++) {
		if (x_count > tex_s - 1)
			x_count = 0;
		for (GLfloat y = -0.5; y < 0.5; y += tile_h, y_count++) {
			if (y_count > tex_t - 1)
				y_count = 0;
			glBegin(GL_POLYGON);
			glTexCoord2f((GLfloat)x_count * ftex_s, (GLfloat)y_count * ftex_t);
			glVertex3f(x, y, 0);

			glTexCoord2f((GLfloat)x_count * ftex_s + ftex_s, (GLfloat)y_count * ftex_t);
			glVertex3f(x + tile_w, y, 0);

			glTexCoord2f((GLfloat)x_count * ftex_s + ftex_s, (GLfloat)y_count * ftex_t + ftex_t);
			glVertex3f(x + tile_w, y + tile_h, 0);

			glTexCoord2f((GLfloat)x_count * ftex_s, (GLfloat)y_count * ftex_t + ftex_t);
			glVertex3f(x, y + tile_h, 0);
			glEnd();
		}
	}
}

void drawAxis() {
	glPushMatrix();
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glPopMatrix();

	glColor3f(1, 1, 1);
}

void drawTableLeg() {
	glPushMatrix();
	glScalef(TABLE_LEG_WIDTH, TABLE_HEIGHT, TABLE_LEG_WIDTH);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawTable() {
	glColor3f(0, 1, 1);
	glPushMatrix();

	glTranslatef(0, TABLE_HEIGHT, 0);

	glPushMatrix();
	glTranslatef(0, TABLE_LEG_WIDTH / 2.0, 0);
	glScalef(TABLE_WIDTH, TABLE_LEG_WIDTH, TABLE_LENGTH);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-TABLE_WIDTH / 2 + TABLE_LEG_WIDTH, -TABLE_HEIGHT / 2, -TABLE_LENGTH / 2 + TABLE_LEG_WIDTH);
	drawTableLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-TABLE_WIDTH / 2 + TABLE_LEG_WIDTH, -TABLE_HEIGHT / 2, TABLE_LENGTH / 2 - TABLE_LEG_WIDTH);
	drawTableLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(TABLE_WIDTH / 2 - TABLE_LEG_WIDTH, -TABLE_HEIGHT / 2, -TABLE_LENGTH / 2 + TABLE_LEG_WIDTH);
	drawTableLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(TABLE_WIDTH / 2 - TABLE_LEG_WIDTH, -TABLE_HEIGHT / 2, TABLE_LENGTH / 2 - TABLE_LEG_WIDTH);
	drawTableLeg();
	glPopMatrix();

	glPopMatrix();
}

void drawCarpet() {
	glColor3f(1, 1, 0);
	glPushMatrix();

	glScalef(CARPET_WIDTH, CARPET_LENGTH, 1);

	drawPlate(20, 40, 20, 40);
	glPopMatrix();
}

void drawFloor() {
	glColor3f(0, 0, 1);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);

	glScalef(FLOOR_WIDTH, FLOOR_LENGTH, 1);

	drawPlate(20, 20, 4, 4);

	glPopMatrix();
}

void drawWalls() {
	glColor3f(0, 1, 0);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);

	glTranslatef(0, 0, FLOOR_LENGTH / 2.0);
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glScalef(FLOOR_WIDTH, FLOOR_LENGTH, 1);
	glTranslatef(0, 0, -FLOOR_LENGTH / 2.0f);
	drawPlate(20, 20, 5, 5);
	glPopMatrix();

	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(FLOOR_WIDTH, FLOOR_LENGTH, 1);
	glTranslatef(0, 0, -FLOOR_WIDTH / 2.0f);
	drawPlate(20, 20, 5, 5);


	glPopMatrix();
}

void drawNewspaperSheet() {
	glPushMatrix();

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, -0.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.3, 0.5, 0);
	glTexCoord2f(0.2, 0);
	glVertex3f(-0.5, -0.5, 0.2);
	glTexCoord2f(0.2, 1);
	glVertex3f(-0.5, 0.5, 0.2);
	glTexCoord2f(0.3, 0);
	glVertex3f(-0.3, -0.5, 0.25);
	glTexCoord2f(0.3, 1);
	glVertex3f(-0.3, 0.5, 0.25);
	glTexCoord2f(0.6, 0);
	glVertex3f(0.1, -0.5, 0.22);
	glTexCoord2f(0.6, 1);
	glVertex3f(0.1, 0.5, 0.22);
	glTexCoord2f(0.8, 0);
	glVertex3f(0.3, -0.5, 0.1);
	glTexCoord2f(0.8, 1);
	glVertex3f(0.3, 0.5, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, -0.5, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, 0.0);
	glEnd();

	glPopMatrix();
}

void drawNewspaper() {
	glColor3f(1, 1, 1);
	glPushMatrix();
	drawNewspaperSheet();
	glScalef(0.8, 1, 0.8);
	glTranslatef(0, -0.01, 0);
	drawNewspaperSheet();
	glScalef(0.8, 1, 0.8);
	glTranslatef(0, -0.05, 0);
	drawNewspaperSheet();
	glScalef(0.8, 1, 0.8);
	glTranslatef(0, -0.1, 0);
	drawNewspaperSheet();
	glPopMatrix();
}

void drawLamp(bool isEnabled) {
	glColor3f(1, 0, 0);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0, LAMP_LENGTH / 2.0, 0);
	glScalef(LAMP_WIRE_WIDTH, LAMP_LENGTH, LAMP_WIRE_WIDTH);
	setTableMaterial();
	glutSolidCube(1);
	glPopMatrix();
	setLampMaterial();
	if(isEnabled)
		enableEmission();
	glutSolidSphere(LAMP_SCALE, 10, 10);
	disableEmission();
	glPopMatrix();
}

void drawBall() {
	glColor3f(1, 0, 0);
	glutSolidSphere(BALL_SCALE / 2.0, 20, 20);
}