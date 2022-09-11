#include "LambertfsShader.h"

LambertfsShader::LambertfsShader()
	:FragmentShader()
{

}


vector3f LambertfsShader::CalcPointLight(FragmentItem item)
{
	vector3f ambient = DiffuseTexture.GetTextureColor(item.texCoord.x, item.texCoord.y) * AmbientStream * light1.ambient;


	vector3f norm = item.Normal.Normalize();
	vector3f LightDir = (LightPosition - item.FragPosition).Normalize();

	float diff = max(vector3f::dot(norm, LightDir), 0.0f);
	vector3f diffuse = DiffuseTexture.GetTextureColor(item.texCoord.x, item.texCoord.y) * light1.diffuse * diff;
	return ambient + diffuse;
}


Color LambertfsShader::CalculateColor(FragmentItem item)
{
	if (DiffuseTexture.IsVaild())
	{
		cout << "error DiffuseTexture is NULL" << endl;
		return Color::White();
	}
	vector3f ambient = LightColor * AmbientStream;

	vector3f norm = item.Normal.Normalize();
	vector3f LightDir = (LightPosition - item.FragPosition).Normalize();

	float diff = max(vector3f::dot(norm, LightDir), 0.0f);
	vector3f diffuse = LightColor * diff;

	Color DefColor = Color((diffuse + ambient) * ObjectColor);

	Color Result = CalcPointLight(item);
	if (Result.r > 0.5)
		cout << "  " << endl;
	return Result;
}
