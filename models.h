#pragma once

//параметры стола
#define TABLE_WIDTH 7.0
#define TABLE_LENGTH 5.0
#define TABLE_HEIGHT 4.0
#define TABLE_LEG_WIDTH 0.5

//параметры ковра
#define CARPET_WIDTH 6.0
#define CARPET_LENGTH 12.0

//параметры пола
#define FLOOR_WIDTH 15.0
#define FLOOR_LENGTH 15.0
#define FLOOR_DIVISION 150

//параметры газеты
#define NEWS_LENGTH 1.0

//высота лампочки над полом
#define BULB_HEIGHT 16.0f

//параметры лампочки
#define LAMP_LENGTH 2.0
#define LAMP_WIRE_WIDTH 0.1
#define LAMP_SCALE 0.2

//параметры шара
#define BALL_SCALE 1.0

//установить материал ковра
void setCarpetMaterial();
//установить материал пола
void setFloorMaterial();
//установить материал стен
void setWallMaterial();
//установить материал стола
void setTableMaterial();
//установить материал газеты
void setNewspaperMaterial();
//установить материал лампы
void setLampMaterial();
//установить материал шара
void setBallMaterial();

//включить свечение материала
void enableEmission();
//выключить свечение материала
void disableEmission();

//нарисовать квадрат 1 на 1 состоящий из width * height полигонов и текстурой лежащей на прямоугольнике из tex_s * tex_t полигонов
void drawPlate(int width, int height, int tex_s, int tex_t);
//нарисовать ось (так и не использовалась)
void drawAxis();
//нарисовать стол
void drawTable();
//нарисовать ковер
void drawCarpet();
//нарисовать пол
void drawFloor();
//нарисовать стены
void drawWalls();
//нарисовать газетный лист
void drawNewspaperSheet();
//нарисовать газету
void drawNewspaper();
//нарисовать лампочку (в зависимости от значения параметра, она будет светиться и наоборот)
void drawLamp(bool isEnabled);
//нарисовать шар
void drawBall();
