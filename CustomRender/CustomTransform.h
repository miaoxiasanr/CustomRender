#ifndef CUSTOMTRANSFORM_H
#define CUSTOMTRANSFORM_H
#include "CustomVector.h"
#include "CustomMatrix.h"
#include "CustomMath.h"
#include "Configure.h"
class Transform
{
public:
	vector3f position;
	vector3f rotation;
	vector3f scale;
	Matrix objectToWorld;
public:
	Transform();
	Transform(vector3f Pos, vector3f Rot, vector3f Sca);
	Matrix Translate(const vector3f& v);
	Matrix Rotate(const vector3f& RotAngle);
	Matrix RotateX(const float& angle);
	Matrix RotateY(const float& angle);
	Matrix RotateZ(const float& angle);
	Matrix Scale(const vector3f& Sca);
};
#endif


