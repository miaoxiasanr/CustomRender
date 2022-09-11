#include "CustomTransform.h"

Transform::Transform()
	:scale(1.0f,1.0f,1.0f)
{
	objectToWorld.Identity();
}

Transform::Transform(vector3f Pos, vector3f Rot, vector3f Sca)
	:position(Pos),rotation(Rot),scale(Sca)
{

}

Matrix Transform::Translate(const vector3f& v)
{
	position = v;
	Matrix m;
	m.value[0][3] = v.x;
	m.value[1][3] = v.y;
	m.value[2][3] = v.z;
	return m;

}

Matrix Transform::Rotate(const vector3f& RotAngle)
{
	rotation = RotAngle;
	Matrix rotX=RotateX(RotAngle.x);
	Matrix rotY = RotateY(RotAngle.y);
	Matrix rotZ = RotateZ(RotAngle.z);
	return rotX*rotY*rotZ;
}

Matrix Transform::RotateX(const float& angle)
{
	rotation.x = angle;
	Matrix m;
	float radius = angle / 360.f * PI;
	float sinvalue = sin(radius);
	float cosvalue = cos(radius);
	m.value[1][1] = cosvalue;
	m.value[1][2] = sinvalue;
	m.value[2][1] = -sinvalue;
	m.value[2][2] = cosvalue;
	return m;
}

Matrix Transform::RotateY(const float& angle)
{
	rotation.y = angle;
	Matrix m;
	float radius = angle / 360.f * PI;
	float sinvalue = sin(radius);
	float cosvalue = cos(radius);
	m.value[0][0] = cosvalue;
	m.value[0][2] = -sinvalue;
	m.value[2][0] = sinvalue;
	m.value[2][2] = cosvalue;
	return m;
}

Matrix Transform::RotateZ(const float& angle)
{
	rotation.z = angle;
	Matrix m;
	float radius = angle / 360.f * PI;
	float sinvalue = sin(radius);
	float cosvalue = cos(radius);
	m.value[0][0] = cosvalue;
	m.value[0][1] = sinvalue;
	m.value[1][0] = -sinvalue;
	m.value[1][1] = cosvalue;
	return m;
}

Matrix Transform::Scale(const vector3f& Sca)
{
	rotation = Sca;
	Matrix m;
	m.value[0][0] = Sca.x;
	m.value[1][1] = Sca.y;
	m.value[2][2] = Sca.z;
	return m;
}
