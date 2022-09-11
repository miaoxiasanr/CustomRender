#ifndef CUSTOMFRAGMENT_H
#define CUSTOMFRAGMENT_H
#include "CustomColor.h"
#include "CustomVector.h"
#include "QImage"
#include "CustomTexture.h"

#include "Configure.h"
struct FragmentItem
{
	vector2f texCoord;
	vector3f Normal;
	vector3f FragPosition;

};

struct PointLight
{
	vector3f LightPosition;

	float constant;
	float linear;
	float quadratic;

	vector3f ambient;
	vector3f diffuse;
	vector3f specular;
};
class FragmentShader
{
public:
	float AmbientStream;
	Texture DiffuseTexture;
	Texture SpecularTexture;
	vector3f LightPosition;
	vector3f LightColor;
	vector3f ObjectColor;
public:
	FragmentShader();
	virtual Color CalculateColor(FragmentItem item);


	
};

#endif

