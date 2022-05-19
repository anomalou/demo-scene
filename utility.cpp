#include "utility.h"

void initTextures() {
	ilInit();
	ilutRenderer(ILUT_OPENGL);

	texturesBase.insert(make_pair("none", 0));
	registerTexture(ilLoadTexture(L"C:/labs/Semestr 6/Graphics/resultwork/resultwork/bmp/pnewspaper.png"), "newspaper");
	registerTexture(ilLoadTexture(L"C:/labs/Semestr 6/Graphics/resultwork/resultwork/bmp/table.png"), "table");
	registerTexture(ilLoadTexture(L"C:/labs/Semestr 6/Graphics/resultwork/resultwork/bmp/floor.png"), "floor");
	registerTexture(ilLoadTexture(L"C:/labs/Semestr 6/Graphics/resultwork/resultwork/bmp/wall.png"), "wall");
	registerTexture(ilLoadTexture(L"C:/labs/Semestr 6/Graphics/resultwork/resultwork/bmp/carpet.png"), "carpet");
}

Texture ilLoadTexture(wstring path) {
	Texture texture = { 0 };

	ILuint texName[1];
	ilGenImages(1, texName);
	ilBindImage(texName[0]);

	ilLoadImage(path.c_str());
	iluRotate(180);

	texture.width = ilGetInteger(IL_IMAGE_WIDTH);
	texture.height = ilGetInteger(IL_IMAGE_HEIGHT);
	texture.dataType = GL_UNSIGNED_BYTE;
	texture.format = GL_RGBA;
	texture.data = new unsigned char[texture.width * texture.height * 4];
	ilCopyPixels(0, 0, 0, texture.width, texture.height, 1, IL_RGBA, IL_UNSIGNED_BYTE, texture.data);

	ilBindImage(0);

	return texture;
}

void registerTexture(Texture texture, string byName) {

	GLuint textureID;
	glGenTextures(1, &textureID);

	texturesBase.insert(make_pair(byName, textureID));

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, texture.format, texture.width, texture.height, 0, texture.format, texture.dataType, texture.data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_SRC_ALPHA);

	delete texture.data;

	glBindTexture(GL_TEXTURE_2D, 0);
}

void useTexture(string name) {
	GLuint texID = texturesBase.at(name);
	glBindTexture(GL_TEXTURE_2D, texID);
}