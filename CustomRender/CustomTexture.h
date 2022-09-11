#ifndef CUSTOMTEXTURE_H
#define CUSTOMTEXTURE_H
#include "QImage"
#include "iostream"
#include "CustomColor.h"
#include "Configure.h"
using namespace std;
class Texture
{
public:
	Texture();
	Texture(const char* filename);
	QImage GetTexture();

	bool IsVaild();
	Color GetTextureColor(float width, float height);
public:
	QImage texture;
	int Width=0;
	int Height=0;
};

#endif // CUSTOMTEXTURE_H

