#ifndef IMAGEINSTANCE_H
#define IMAGEINSTANCE_H
#include "iostream"
#include "ImageBuffer.h"
#include "CustomVector.h"
#include "CustomColor.h"
#include "CustomVertex.h"
#include "LoadModel.h"
#include "CustomCamera.h"
#include "CustomTransform.h"
#include "FragmentShader.h"
#include "CustomMatrix.h"
#include "Configure.h"
#include "VertexShader.h"

class ImageInstance
{
protected:
	ImageInstance();
public:
	ImageBuffer buffer;
public:

	~ImageInstance();

	ImageInstance(ImageInstance&) = delete;
	ImageInstance& operator=(ImageInstance&) = delete;

	static ImageInstance& GetInstance();
	void ClearImage();
	void FillImage();

	//��׶���޳���Ҫ��һ�½������
	// 1.�����ΧҪ���������AABB��(��������)
	// 2.�����׶���������ƽ�淽��(��������)
	// 3.�ж�AABB�е���С��������Ƿ�����������ڲ�����
	// 4.�޳�����С��������ȫ��ĳһ����������
	vector<vector3f> UpdateViewPlanes( Matrix& vp);

	bool ViewCull(const vector3f& p1, const vector3f& p2, const vector3f& p3,VertexShader&vsShader);
	//�ӿ��޳�
	vector<vector3f> ViewLine =
	{
		vector3f(1.f,0.f,-1.f),//x=1;
		vector3f(0.f,1.f,-1.f),//y=1
		vector3f(-1.f,0.f,-1.f),//x=-1
		vector3f(0.f,-1.f,-1.f)//y=-1
	};
	bool AllVertexInside(const vector3f& p1, const vector3f& p2, const vector3f& p3);
	//Sutherland-Hodgman�㷨
	vector<vector3f> ViewportCulling(const vector3f& p1, const vector3f& p2, const vector3f& p3);

	//�����㷨
	void DrawLine(vector2i Begin, vector2i end, Color LineColor);
	void DrawDDALine(vector2i Begin, vector2i end, Color LineColor);
	void DrawBresenhamLine(vector2i Begin, vector2i end, Color LineColor);

	void DrawBresenhamLine(vector3f Begin, vector3f end, Color LineColor);



	//������Χ��
	vector<vector2i> CreateBoundBox(vector<vector3f> t);
	

	//��������
	void DrawTriangle(vertex t0, vertex t1, vertex t2,FragmentShader*fsShader);
	void DrawTriangle(vector2i t0, vector2i t1, vector2i t2, Color TriangeleColor);
	void DrawTriangle(vector3f t0, vector3f t1, vector3f t2, Color TriangeleColor);


	//��ģ��
	//�߿�ģ��
	void DrawWireframeModel(LoadModel* model);

	void DrawWireframeModel(LoadModel* model, VertexShader& vsShader);

	//��ɫģ��
	void DrawPureModel(LoadModel* model);

	//�����µĴ�ɫģ��
	void DrawModelWIthBaseLighting(LoadModel* model);

	//ZBufferģ��
	void DrawModelWithZBuffer(LoadModel* model);

	//�������㻭ģ��
	void DrawModelWithVertex(LoadModel* model, VertexShader& vsShader);

	//�����ƬԪ
	void DrawModelWithFragment(LoadModel* model,VertexShader &vsShader,FragmentShader *fsShader);
};
#endif



