#ifndef CUSTOMVERTEX_H
#define CUSTOMVERTEX_H
#include "CustomMatrix.h"
#include "iostream"
using namespace std;
class vertex
{

public:
	//顶点信息应该输出不限于屏幕坐标，深度值，顶点颜色，法线，纹理坐标
	vector3f LocalObjectPosition;
	vector3f WorldSpacePosition;
	vector3f ClipSpacePosition;//裁剪空间坐标
	vector3f NDCSpacePosition;//标椎化设备坐标 将裁剪空间坐标的(-w,-w,-w)变换成(-1,-1,-1).
	vector3f ScreenSpacePostionNoFilp;
	vector3f Normal;
	vector2f uv;
	vector3f ScreenSpacePostion;
	float ScreenDepth=0.f;

public:
	vertex();
	vertex(vector3f localpos);
	vertex(vector3f localpos,vector3f normal,vector2f uv_);
	vector3f CalculateMatrix(const Matrix&view,const Matrix& model,const Matrix& projection,const Matrix&viewport);

	vector3f CalculateMatrix(const Matrix& viewport);



};

#endif

