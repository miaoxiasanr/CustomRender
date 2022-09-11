#include "Blinn_PhongfsShader.h"
#include "CustomMath.h"
Blinn_PhongfsShader::Blinn_PhongfsShader()
	:FragmentShader(), CameraLocation(DefaultCameraLocation), specularStreangth(0.3f)
{

}

vector3f Blinn_PhongfsShader::CalcPointLight(FragmentItem item)
{
	vector3f ambient = DiffuseTexture.GetTextureColor(item.texCoord.x, item.texCoord.y)* AmbientStream*light1.ambient ;


	vector3f norm = item.Normal.Normalize();
	vector3f LightDir = (LightPosition - item.FragPosition).Normalize();

	float diff = max(vector3f::dot(norm, LightDir), 0.0f);
	vector3f diffuse = DiffuseTexture.GetTextureColor(item.texCoord.x, item.texCoord.y) * light1.diffuse * diff;

	vector3f viewDir = (CameraLocation - item.FragPosition).Normalize();
	vector3f halfwryDir = (LightDir + viewDir).Normalize();


	float spec = pow(max(vector3f::dot(norm, halfwryDir), 0.f), 128.f);
	vector3f specular =SpecularTexture.GetTextureColor(item.texCoord.x, item.texCoord.y)* light1.specular * specularStreangth * spec;

	float distance = Length(light1.LightPosition , item.FragPosition);
	float attenuation = 1.0 / (light1.constant + light1.linear * distance + light1.quadratic * (distance * distance));


	ambient = ambient* attenuation;
	diffuse = diffuse* attenuation;
	specular = specular* attenuation;

	return ambient + diffuse + specular;
}

Color Blinn_PhongfsShader::CalculateColor(FragmentItem item)
{
	if (DiffuseTexture.IsVaild() || SpecularTexture.IsVaild())
	{
		string error;
		DiffuseTexture.IsVaild() ? error = "error DiffuseTexture is NULL" : error = "error SpecularTexture is NULL";
		cout << error << endl;
		return Color::White();
	}

	//环境光
	vector3f ambient = LightColor * AmbientStream;

	//漫反射
	vector3f norm = item.Normal.Normalize();
	vector3f LightDir = (LightPosition - item.FragPosition).Normalize();

	float diff = max(vector3f::dot(norm, LightDir), 0.0f);
	vector3f diffuse = LightColor * diff;

	//镜面反射
	vector3f viewDir = (CameraLocation - item.FragPosition).Normalize();
	vector3f halfwryDir = (LightDir + viewDir).Normalize();


	float spec = pow(max(vector3f::dot(norm,halfwryDir), 0.f), 128.f);
	vector3f specular = LightColor * specularStreangth * spec;
	Color DefColor = Color((diffuse + ambient + specular) * DefauitObjectColor);

	Color Result = CalcPointLight(item);
	return Result;
}
