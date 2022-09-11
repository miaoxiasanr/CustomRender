#ifndef LAMBERTFRAGMENT_H
#define LAMBERTFRAGMENT_H
#include "FragmentShader.h"
class LambertfsShader :public FragmentShader
{
public:
	PointLight light1;
public:
	LambertfsShader();
	vector3f CalcPointLight(FragmentItem item);
	Color CalculateColor(FragmentItem item)override;
};
#endif
