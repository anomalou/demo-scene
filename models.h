#pragma once

#define TABLE_WIDTH 2.0
#define TABLE_LENGTH 2.0
#define TABLE_HEIGHT 1.0

#define CARPET_WIDTH 3.0
#define CARPET_LENGTH 4.0

#define FLOOR_WIDTH 15.0
#define FLOOR_LENGTH 15.0
#define FLOOR_DIVISION 150

#define NEWS_LENGTH 1.0

void setCarpetMaterial();
void setFloorMaterial();
void setTableMaterial();
void setNewspaperMaterial();
void setCoffeeMaterial();
void setCupMaterial();

void drawPlate(int width, int height, int tex_s, int tex_t);
void drawAxis();
void drawTable();
void drawCarpet();
void drawFloor();
void drawNewspaperSheet();
void drawNewspaper();
void drawLamp();
