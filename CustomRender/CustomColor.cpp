#include "CustomColor.h"

Color::Color(float _r, float _g, float _b, float _a)
{
	r = _r >= 1.f ? 1.f : _r;
	g = _g >= 1.f ? 1.f : _g;
	b = _b >= 1.f ? 1.f : _b;
	a = _a >= 1.f ? 1.f : _a;
}

Color::Color(float _r, float _g, float _b)
{
	r = _r >= 1.f ? 1.f : _r;
	g = _g >= 1.f ? 1.f : _g;
	b = _b >= 1.f ? 1.f : _b;
}

Color::Color()
	:r(1.0), g(1.0), b(1.0), a(1.0)
{
	
}

Color::Color(vector3f v)
{
	r = v.x >= 1.f ? 1.f : v.x;
	g = v.y >= 1.f ? 1.f : v.y;
	b = v.z >= 1.f ? 1.f : v.z;
	a = v.w >= 1.f ? 1.f : v.w;

}

Color::~Color()
{

}

Color Color::White()
{
	return Color(1.f, 1.f, 1.f, 1.f);
}

Color Color::operator+(const Color& c) 
{
	this->r += c.r;
	this->g += c.g;
	this->b += c.b;
	this->a += c.a;
	return *this;
}

Color Color::operator+(const float& c) 
{
	this->r += c;
	this->g += c;
	this->b += c;
	this->a += c;
	return *this;
}

Color Color::operator*(const Color& c) 
{
	this->r *= c.r;
	this->g *= c.g;
	this->b *= c.b;
	this->a *= c.a;
	return *this;
}

Color Color::operator*(float& c) 
{
	this->r *= c;
	this->g *= c;
	this->b *= c;
	this->a *= c;
	return *this;
}

vector3f Color::operator*(const vector3f& c)
{
	vector3f ret;
	ret.x =r *  c.x;
	ret.y =g *  c.y;
	ret.z =b *  c.z;
	ret.w =a *  c.w;
	return ret;
}

Color Color::operator/(float& c) 
{
	this->r /= c;
	this->g /= c;
	this->b /= c;
	this->a /= c;
	return *this;
}


void Color::debug()
{
	cout << r << " ";
	cout << g << " ";
	cout << b << " ";
	cout << a << " ";
	cout << endl;
}

Color Color::operator=(const Color& c) 
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
	this->a = c.a;
	return *this;

}

bool  Color::operator!=(const Color& c)const
{
	return r != c.r || g != c.g || b != c.b ;
}
