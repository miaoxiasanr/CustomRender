#ifndef CUSTOMVERTEX_H
#define CUSTOMVERTEX_H
#include "CustomMatrix.h"
#include "iostream"
using namespace std;
class vertex
{

public:
	//������ϢӦ�������������Ļ���꣬���ֵ��������ɫ�����ߣ���������
	vector3f LocalObjectPosition;
	vector3f WorldSpacePosition;
	vector3f ClipSpacePosition;//�ü��ռ�����
	vector3f NDCSpacePosition;//��׵���豸���� ���ü��ռ������(-w,-w,-w)�任��(-1,-1,-1).
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

