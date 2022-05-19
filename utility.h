#pragma once

#ifndef UTILITY_H
#define UTILITY_H

#include <GL/glut.h>
#include <string>
#include <IL/ilut.h>
#include <map>

#pragma comment(lib, "DevIL.lib")
#pragma comment(lib, "ILU.lib")
#pragma comment(lib, "ILUT.lib")

using namespace std;

//структура с данными текстуры
typedef struct _texture {
	unsigned char* data;
	int width;
	int height;
	GLint format;
	GLenum dataType;
} Texture;

//словарь для более удобного использования текстур по строковым именам
static map<string, GLuint> texturesBase;

//инициализация текстур и их загрузка 
void initTextures();

//загрузить текстуру из файла с помощью DevIL
Texture ilLoadTexture(wstring path);
//создать текстуру в opengl из полученных текстелей
void registerTexture(Texture texture, string byName);
//установить текстуру текущей в конвеере opengl по строковому имени
void useTexture(string name);

#endif
