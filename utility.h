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

typedef struct _texture {
	unsigned char* data;
	int width;
	int height;
	GLint format;
	GLenum dataType;
} Texture;

static map<string, GLuint> texturesBase;

void initTextures();

Texture ilLoadTexture(wstring path);
void registerTexture(Texture texture, string byName);
void useTexture(string name);

#endif
