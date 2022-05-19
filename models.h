#pragma once

#define TABLE_WIDTH 7.0
#define TABLE_LENGTH 5.0
#define TABLE_HEIGHT 4.0
#define TABLE_LEG_WIDTH 0.5

#define CARPET_WIDTH 6.0
#define CARPET_LENGTH 12.0

#define FLOOR_WIDTH 15.0
#define FLOOR_LENGTH 15.0
#define FLOOR_DIVISION 150

#define NEWS_LENGTH 1.0

#define LAMP_LENGTH 2.0
#define LAMP_WIRE_WIDTH 0.1
#define LAMP_SCALE 0.2

#define BALL_SCALE 1.0

#define BULB_HEIGHT 16.0f

void setCarpetMaterial();
void setFloorMaterial();
void setWallMaterial();
void setTableMaterial();
void setNewspaperMaterial();
void setLampMaterial();
void setBallMaterial();

void enableEmission();
void disableEmission();

void drawPlate(int width, int height, int tex_s, int tex_t);
void drawAxis();
void drawTable();
void drawCarpet();
void drawFloor();
void drawWalls();
void drawNewspaperSheet();
void drawNewspaper();
void drawLamp(bool isEnabled);
void drawBall();
