#pragma once
#include "FragmentShader.h"
class Blinn_PhongfsShader :
    public FragmentShader
{
public:
	vector3f CameraLocation;
	float specularStreangth;
    PointLight light1;
public:
    Blinn_PhongfsShader();
    vector3f CalcPointLight(FragmentItem item);
    Color CalculateColor(FragmentItem item)override;
};

