#include "FragmentShader.h"



FragmentShader::FragmentShader()
	:AmbientStream(0.01f),LightColor(DefaultLightColor),LightPosition(DefaultLightPosition), ObjectColor(DefauitObjectColor)
{

}

Color FragmentShader::CalculateColor(FragmentItem item)
{
	return LightColor;
}

