#include "CustomTexture.h"

Texture::Texture(const char* filename)
{
	if (!texture.load(filename))
	{
		cout << "texture load failed" << endl;
	}
	else
	{
		Width = texture.width();
		Height = texture.height();
	}
	

}

Texture::Texture()
{

}

QImage Texture::GetTexture()
{
	return texture;
}

bool Texture::IsVaild()
{
	return texture.isNull();
}

Color Texture::GetTextureColor(float width, float height)
{
	int x = static_cast<int>(width * Width-0.5 ) % Width;
	int y = static_cast<int>(height * Height-0.5 ) % Height;
	x = x < 0 ? Width + x : x;
	y = y < 0 ? Height + y : y;
	return Color(texture.pixelColor(x, y).red() / 255.f, texture.pixelColor(x, y).green() / 255.f, texture.pixelColor(x,y).blue() / 255.f);
}
