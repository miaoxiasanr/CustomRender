#ifndef CUSTOMMATH_H
#define CUSTOMMATH_H


#include "CustomVector.h"
#include "Configure.h"
#include "CustomMatrix.h"
#include "CustomVertex.h"


float Clamp(float x, float min, float max);

float Radians(float Angle);

int ToInt(float v);

vector3f CenterOfGravity2D(vector2i v1, vector2i v2, vector2i v3, vector2i p);

vector3f CenterOfGravity3D(vector3f v1, vector3f v2, vector3f v3, vector3f p);

float LerpDepth(float a, float b, float c, vector3f& CenterOfGravity);

vector3f Lerp(const vector3f& p1, const vector3f& p2, const float& weight);

vector3f ToPoint(const vector3f& v);

//判断是否在视口内
bool IsInside(const vector3f& Line, const vector3f& Point);

//求交点
vector3f Intersert(const vector3f& Point1, const vector3f& Point2, const vector3f& Line);

bool PointToPlane(const vector3f& v, const vector3f& p);

vector3f FilpHeight(vector3f res);

vector3f Reflect(const vector3f& InDir, const vector3f& nor);

float Length(const vector3f& begin, const vector3f& end);

Matrix LookAt(const vector3f& Pos, const vector3f& Lookat, const vector3f& Up);

Matrix Perspective(float fov, float aspect, float Near, float Far);

Matrix Perspective(float l, float r, float n, float f, float t, float b);

Matrix Orthographic(float l, float r, float n, float f, float t, float b);

Matrix ViewPort(int x, int y, int width, int height);

Matrix BackToOrigin(const Matrix& m);

Matrix BackToNormal(Matrix&  origin,const  Matrix& m);

Matrix LinerTransform(const Matrix& Transform, const  Matrix& NormalMatrix);

Matrix Translate(Matrix& m, const vector3f& v);

Matrix Rotate(Matrix& m, const vector3f& RotAngle);

Matrix Rotate(Matrix& m, const float& angle, const vector3f& Axis);

Matrix RotateX(Matrix& m, const float& angle);

Matrix RotateY(Matrix& m, const float& angle);

Matrix RotateZ(Matrix& m, const float& angle);

Matrix Scale(Matrix& m, const vector3f& Sca);



template<class T>
T CalculateInterpolation(T v0, T v1, T v2, vector3f& barycentric);


template<class T>
T CalculateInterpolation(T v0, T v1, T v2, vector3f& barycentric)
{
	return v0 * barycentric.x + v1 * barycentric.y + v2 * barycentric.z;
}


//vector2f CalculateInterpolation(vertex tri[3], vector2f attribute[3], vector3f barycentric, float dep)
//{
//	return  (attribute[0] * barycentric.x / tri[0].ClipSpacePosition.w + attribute[1] * barycentric.y / tri[1].ClipSpacePosition.w + attribute[2] * barycentric.z / tri[2].ClipSpacePosition.w) * dep;
//}

#endif


