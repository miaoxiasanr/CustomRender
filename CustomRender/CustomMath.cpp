#include "CustomMath.h"


float Clamp(float x, float min, float max)
{
	if (x>max)
	{
		x = max;
	}
	if (x<min)
	{
		x = min;
	}
	return x;
}

float Radians(float Angle)
{
	return Angle * (PI / 180.);
}

int  ToInt(float v)
{

	return  v > 0.5 ? int(v + 1) : int(v);


}

vector3f CenterOfGravity2D(vector2i v1, vector2i v2, vector2i v3, vector2i p)
{
	vector3f res=vector3f::Cross(vector3f(v3.x - v1.x, v2.x - v1.x, v1.x - p.x), vector3f(v3.y - v1.y, v2.y - v1.y, v1.y - p.y));
	if (abs(res.z)<1)
	{
		return vector3f(-1., -1., -1.);
	}

	return vector3f(1.f - (res.x + res.y) / res.z, 
						res.y / res.z,
						res.x / res.z);
}

vector3f CenterOfGravity3D(vector3f v1, vector3f v2, vector3f v3, vector3f p)
{
	vector3f s1=vector3f(v3.x-v1.x,v2.x-v1.x,v1.x-p.x);
	vector3f s2 = vector3f(v3.y - v1.y, v2.y - v1.y, v1.y - p.y);
	vector3f res = vector3f::Cross(s1, s2);
	//if (abs(u.z > 1e-2))
	//{
	//	return vector3f(1.f - (u.x + u.y) / u.z, u.y / u.x, u.x / u.z);
	//}
	//return vector3f(-1.f, -1.f, -1.f);
	if (abs(res.z) < 1)
	{
		return vector3f(-1., -1., -1.);
	}

	return vector3f(1.f - (res.x + res.y) / res.z,
		res.y / res.z,
		res.x / res.z);

}


float LerpDepth(float a, float b, float c, vector3f& CenterOfGravity)
{
	return a * CenterOfGravity.x + b * CenterOfGravity.y + c * CenterOfGravity.z;
}

vector3f Lerp(const vector3f& p1, const vector3f& p2, const float &weight)
{
	vector3f ret;
	ret.x = p1.x * (1 - weight) + p2.x * weight;
	ret.y = p1.y * (1 - weight) + p2.y * weight;
	ret.z = p1.z * (1 - weight) + p2.z * weight;
	return ret;
}

vector3f ToPoint(const vector3f& v)
{
	return vector3f(v.x/v.w,v.y/v.w,v.z/v.w,v.w/v.w);
	
}

//ax+by+c=0
bool IsInside(const vector3f& Line, const vector3f& Point)
{
	if (Line.z > 0)
	{
		return Line.x * Point.x + Line.y * Point.y + Line.z > 0;
	}
	else if (Line.z < 0)
	{
		return Line.x * Point.x + Line.y * Point.y + Line.z < 0;
	}
}

vector3f Intersert(const vector3f& Point1, const vector3f& Point2, const vector3f& Line)
{
	if (Line.x == -1)
	{
		float weight = (-1 - Point1.x) / (Point2.x - Point1.x);
		return Lerp(Point1, Point2, weight);
	}
	if (Line.x == 1)
	{
		float weight = (1 - Point1.x) / (Point2.x - Point1.x);
		return Lerp(Point1, Point2, weight);
	}
	if (Line.y == -1)
	{
		float weight = (-1 - Point1.y) / (Point2.y - Point1.y);
		return Lerp(Point1, Point2, weight);
	}
	if (Line.y == 1)
	{
		float weight = (1 - Point1.y) / (Point2.y - Point1.y);
		return Lerp(Point1, Point2, weight);
	}
}

bool PointToPlane(const vector3f& v, const vector3f& p)
{
	return p.x * v.x + p.y * v.y + p.z * v.z + p.w >= 0;
}

Matrix Translate(Matrix& m, const  vector3f& v)
{
	Matrix ret=m;
	ret.value[0][3] = m.value[0][3]+ v.x;
	ret.value[1][3] = m.value[1][3] + v.y;
	ret.value[2][3] = m.value[2][3] + v.z;
	return ret;
}

vector3f FilpHeight(vector3f res)
{
	return vector3f(res.x, Default_Height - res.y, res.z);
}



vector3f Reflect(const vector3f& InDir, const vector3f& nor)
{
	return InDir -  nor * vector3f::dot(InDir ,nor) * 2;
}

float Length(const vector3f& begin, const vector3f& end)
{
	return sqrt((end.x - begin.x) * (end.x - begin.x) * (end.y - begin.y) * (end.y - begin.y) + (end.z - begin.z) * (end.z - begin.z));
}

//https://learnopengl-cn.github.io/01%20Getting%20started/09%20Camera/
Matrix LookAt(const vector3f& Pos, const vector3f& Lookat, const vector3f& Up)
{
	//没有摄像机这一概念，通过吧场景中所有物体往反方向移动来模拟摄像机
	vector3f LookDir = Pos - Lookat;//Z轴方向
	LookDir.Normalize();

	vector3f RightDir = vector3f::Cross(Up, LookDir);
	RightDir.Normalize();

	vector3f UpDir = vector3f::Cross(LookDir, RightDir);
	UpDir.Normalize();

	Matrix m;
	m.value[0][0] = RightDir.x;		m.value[0][1] = RightDir.y;		m.value[0][2] = RightDir.z;		m.value[0][3] = -Pos.x;
	m.value[1][0] = UpDir.x;		m.value[1][1] = UpDir.y;		m.value[1][2] = UpDir.z;		m.value[1][3] = -Pos.y;
	m.value[2][0] = LookDir.x;		m.value[2][1] = LookDir.y;		m.value[2][2] = LookDir.z;		m.value[2][3] = -Pos.z;
	m.value[3][0] = 0;				m.value[3][1] = 0;				m.value[3][2] = 0;				m.value[3][3] = 1;

	return m;

}

Matrix Perspective(float fov, float aspect, float Near, float Far)
{
	Matrix m;
	float tanvalue = tan(0.5f * fov * (PI / 180.));
	m.value[0][0] = 1 / (tanvalue * aspect);	m.value[0][1] = 0;					m.value[0][2] = 0;								m.value[0][3] = 0;
	m.value[1][0] = 0;							m.value[1][1] = 1 / tanvalue;		m.value[1][2] = 0;								m.value[1][3] = 0;
	m.value[2][0] = 0;							m.value[2][1] = 0;					m.value[2][2] = -(Far + Near) / (Far - Near);	m.value[2][3] = -(2 * Near * Far) / (Far - Near);
	m.value[3][0] = 0;							m.value[3][1] = 0;					m.value[3][2] = -1;								m.value[3][3] = 0;

	return m;

}

Matrix Perspective(float l, float r, float n, float f, float t, float b)
{
	Matrix m;
	m.value[0][0] = 2 * n / (r - l);	m.value[0][1] = 0;					m.value[0][2] = (r + l) / (r - l);	m.value[0][3] = 0;
	m.value[1][0] = 0;					m.value[1][1] = 2 * n / (t - b);	m.value[1][2] = (t + b) / (t - b);	m.value[1][3] = 0;
	m.value[2][0] = 0;					m.value[2][1] = 0;					m.value[2][2] = -(f + n) / (f - n);	m.value[2][3] = (-2 * f * n) / (f - n);
	m.value[3][0] = 0;					m.value[3][1] = 0;					m.value[3][2] = 1;					m.value[3][3] = 0;

	return m;


}

Matrix Orthographic(float l, float r, float n, float f, float t, float b)
{
	Matrix m;
	m.value[0][0] = 2 / (r - l);		m.value[0][1] = 0;					m.value[0][2] = (r + l) / (r - l);	m.value[0][3] = -(r + l) / (r - l);
	m.value[1][0] = 0;					m.value[1][1] = 2 / (t - b);		m.value[1][2] = (t + b) / (t - b);	m.value[1][3] = -(t + b) / (t - b);
	m.value[2][0] = 0;					m.value[2][1] = 0;					m.value[2][2] = -2 / (f - n);		m.value[2][3] = -(f + n) / (f - n);
	m.value[3][0] = 0;					m.value[3][1] = 0;					m.value[3][2] = 0;					m.value[3][3] = 1;


	return m;
}

Matrix ViewPort(int x, int y, int width, int height)
{
	Matrix m;
	m.value[0][0] = width / 2.;			m.value[0][1] = 0;					m.value[0][2] = 0;									m.value[0][3] = width / 2. + x;
	m.value[1][0] = 0;					m.value[1][1] = height / 2.;		m.value[1][2] = 0;									m.value[1][3] = height / 2. + y;
	m.value[2][0] = 0;					m.value[2][1] = 0;					m.value[2][2] = (SCREEN_FAR - SCREEN_NEAR) / 2.;	m.value[2][3] = (SCREEN_FAR + SCREEN_NEAR) / 2.;
	m.value[3][0] = 0;					m.value[3][1] = 0;					m.value[3][2] = 0;									m.value[3][3] = 1;
	return m;
}


Matrix BackToOrigin(const Matrix& m)
{
	Matrix m_ = m;
	m_.value[0][3] = 0.f;
	m_.value[1][3] = 0.f;
	m_.value[2][3] = 0.f;
	return m_;
}

Matrix BackToNormal(Matrix& origin, const Matrix& m)
{
	origin.value[0][3] = m.value[0][3];
	origin.value[1][3] = m.value[1][3];
	origin.value[2][3] = m.value[2][3];
	return origin;
}

Matrix LinerTransform(const Matrix& Transform, const Matrix& NormalMatrix)
{
	Matrix origin = BackToOrigin(NormalMatrix);
	origin = origin * Transform;
	BackToNormal(origin, NormalMatrix);
	return origin;
}

Matrix Rotate(Matrix& m, const vector3f& RotAngle)
{

	Matrix rotX = RotateX( m, RotAngle.x);
	Matrix rotY = RotateY( m, RotAngle.y);
	Matrix rotZ = RotateZ( m, RotAngle.z);
	return rotX * rotY * rotZ;
}

Matrix Rotate(Matrix& m, const float& angle, const vector3f& Axis)
{
	Matrix ret;
	vector3f nor=Axis;
	nor.Normalize();
	float radius = angle / 360.f * PI;
	float sinvalue = sin(radius);
	float cosvalue = cos(radius);
	ret.value[0][0] = nor.x * nor.x * (1 - cosvalue) + cosvalue;
	ret.value[0][1] = nor.x * nor.y * (1 - cosvalue) + nor.z * sinvalue;
	ret.value[0][2] = nor.x * nor.y * (1 - cosvalue) - nor.y * sinvalue;
	ret.value[1][0] = nor.x * nor.y * (1 - cosvalue) - nor.z * sinvalue;
	ret.value[1][1] = nor.y * nor.y * (1 - cosvalue) + cosvalue;
	ret.value[1][2] = nor.y * nor.z * (1 - cosvalue) * nor.x * sinvalue;
	ret.value[2][0] = nor.x * nor.z * (1 - cosvalue) + nor.y * sinvalue;
	ret.value[2][1] = nor.y * nor.z * (1 - cosvalue) - nor.x * sinvalue;
	ret.value[2][2] = nor.z * nor.z * (1 - cosvalue) + cosvalue;
	return LinerTransform(ret, m);
}

Matrix RotateX(Matrix& m, const float& angle)
{
	
	Matrix ret;
	ret.uninitialize();
	float radius = angle / 360.f * PI;
	float sinvalue = sin(radius);
	float cosvalue = cos(radius);
	ret.value[1][1] = cosvalue;
	ret.value[1][2] = sinvalue;
	ret.value[2][1] = -sinvalue;
	ret.value[2][2] = cosvalue;
	return  LinerTransform(ret, m);
}

Matrix RotateY(Matrix& m, const float& angle)
{
	
	Matrix ret;
	ret.uninitialize();
	float radius = angle / 360.f * PI;
	float sinvalue = sin(radius);
	float cosvalue = cos(radius);
	ret.value[0][0] = cosvalue;
	ret.value[0][2] = -sinvalue;
	ret.value[2][0] = sinvalue;
	ret.value[2][2] = cosvalue;
	return  m*ret;
}

Matrix RotateZ(Matrix& m, const float& angle)
{
	
	Matrix ret;
	ret.uninitialize();
	float radius = angle / 360.f * PI;
	float sinvalue = sin(radius);
	float cosvalue = cos(radius);
	ret.value[0][0] = cosvalue;
	ret.value[0][1] = sinvalue;
	ret.value[1][0] = -sinvalue;
	ret.value[1][1] = cosvalue;

	return LinerTransform(ret,m);
}

Matrix Scale(Matrix& m, const vector3f& Sca)
{

	Matrix ret;
	ret.uninitialize();
	ret.SetMatrixByindex(0,m[0] * Sca.x);
	ret.SetMatrixByindex(1,m[1] * Sca.y);
	ret.SetMatrixByindex(2,m[2] * Sca.z);
	ret.SetMatrixByindex(3,m[3]) ;
	return LinerTransform(ret,m);
}



