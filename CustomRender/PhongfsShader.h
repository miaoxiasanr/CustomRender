#pragma once
#include "FragmentShader.h"
class PhongfsShader :
    public FragmentShader
{
public:
    vector3f CameraLocation;
    float specularStreangth;
    PointLight light1;
public:
    PhongfsShader();
    vector3f CalcPointLight(FragmentItem item);
    Color CalculateColor(FragmentItem item)override;
};

