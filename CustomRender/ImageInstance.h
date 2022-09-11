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

	//视锥体剔除主要是一下结果步骤
	// 1.计算包围要绘制物体的AABB盒(世界坐标)
	// 2.获得视锥体六个面的平面方程(世界坐标)
	// 3.判断AABB盒的最小点和最大点是否在六个面的内测或外侧
	// 4.剔除掉最小和最大点完全在某一点外侧的物体
	vector<vector3f> UpdateViewPlanes( Matrix& vp);

	bool ViewCull(const vector3f& p1, const vector3f& p2, const vector3f& p3,VertexShader&vsShader);
	//视口剔除
	vector<vector3f> ViewLine =
	{
		vector3f(1.f,0.f,-1.f),//x=1;
		vector3f(0.f,1.f,-1.f),//y=1
		vector3f(-1.f,0.f,-1.f),//x=-1
		vector3f(0.f,-1.f,-1.f)//y=-1
	};
	bool AllVertexInside(const vector3f& p1, const vector3f& p2, const vector3f& p3);
	//Sutherland-Hodgman算法
	vector<vector3f> ViewportCulling(const vector3f& p1, const vector3f& p2, const vector3f& p3);

	//划线算法
	void DrawLine(vector2i Begin, vector2i end, Color LineColor);
	void DrawDDALine(vector2i Begin, vector2i end, Color LineColor);
	void DrawBresenhamLine(vector2i Begin, vector2i end, Color LineColor);

	void DrawBresenhamLine(vector3f Begin, vector3f end, Color LineColor);



	//构建包围盒
	vector<vector2i> CreateBoundBox(vector<vector3f> t);
	

	//画三角形
	void DrawTriangle(vertex t0, vertex t1, vertex t2,FragmentShader*fsShader);
	void DrawTriangle(vector2i t0, vector2i t1, vector2i t2, Color TriangeleColor);
	void DrawTriangle(vector3f t0, vector3f t1, vector3f t2, Color TriangeleColor);


	//画模型
	//线框模型
	void DrawWireframeModel(LoadModel* model);

	void DrawWireframeModel(LoadModel* model, VertexShader& vsShader);

	//纯色模型
	void DrawPureModel(LoadModel* model);

	//光照下的纯色模型
	void DrawModelWIthBaseLighting(LoadModel* model);

	//ZBuffer模型
	void DrawModelWithZBuffer(LoadModel* model);

	//依靠顶点画模型
	void DrawModelWithVertex(LoadModel* model, VertexShader& vsShader);

	//顶点加片元
	void DrawModelWithFragment(LoadModel* model,VertexShader &vsShader,FragmentShader *fsShader);
};
#endif



