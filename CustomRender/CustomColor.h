#ifndef CUSTOMCPLOR_H
#define CUSTOMCPLOR_H
#include "CustomVector.h"
class Color
{
public:
	float r, g, b, a;
public:
	Color(float _r, float _g, float _b, float _a);
	Color(float _r, float _g, float _b);
	Color(vector3f v);
	Color();
	~Color();

	static Color White();

	Color operator+(const Color& c);
	Color operator+(const float& c);
	Color operator*(const Color& c);
	vector3f operator*(const vector3f& c);
	Color operator*(float& c);
	Color operator/(float& c);
	bool operator!=(const Color& c)const;
	Color operator=(const Color& c);

	void debug();

};
#endif // ifndef 

