#include "ImageInstance.h"



ImageInstance::ImageInstance()
	:buffer(Default_Width, Default_Height)
{

}

ImageInstance::~ImageInstance()
{

}

bool ImageInstance::AllVertexInside(const vector3f& p1, const vector3f& p2, const vector3f& p3)
{
	if (p1.x > 1.f || p1.x < -1.f)
	{
		return false;
	}
	if (p1.y > 1.f || p1.y < -1.f)
	{
		return false;
	}
	if (p2.x > 1.f || p2.x < -1.f)
	{
		return false;
	}
	if (p2.y > 1.f || p2.y < -1.f)
	{
		return false;
	}
	if (p3.x > 1.f || p3.x < -1.f)
	{
		return false;
	}
	if (p3.y > 1.f || p3.y < -1.f)
	{
		return false;
	}
	return true;
}

std::vector<vector3f> ImageInstance::ViewportCulling(const vector3f& p1, const vector3f& p2, const vector3f& p3)
{
	std::vector<vector3f> ret = { p1,p2,p3 };
	for (int i = 0; i < 4; i++)
	{
		std::vector<vector3f> Input = ret;
		ret.clear();
		for (int j = 0; j < Input.size(); j++)
		{
			vector3f CurrPoint = Input[j];
			vector3f Last = Input[(j + Input.size() - 1) % Input.size()];
			if (IsInside(ViewLine[i], CurrPoint))
			{
				if (!IsInside(ViewLine[i], Last))
				{
					vector3f interserting = Intersert(Last, CurrPoint, ViewLine[i]);
					ret.push_back(interserting);
				}
				ret.push_back(CurrPoint);
			}
			else if (IsInside(ViewLine[i], Last))
			{
				vector3f interserting = Intersert(Last, CurrPoint, ViewLine[i]);
				ret.push_back(interserting);
			}
		}
	}
	return ret;
}

void ImageInstance::DrawLine(vector2i Begin, vector2i end, Color LineColor)
{
	for (float t = 0; t < 1.0f; t += 0.001)
	{
		int x = Begin.x + (end.x - Begin.x) * t;
		int y= Begin.y + (end.y - Begin.y) * t;
		buffer.DrawPixel(x, y, LineColor);
	}
}
/////////////////////////////DDA数值微分法///////////////
/*
* 当前步的y值等于前一步的y值加上斜率k
*/
void ImageInstance::DrawDDALine(vector2i Begin, vector2i end, Color LineColor)
{
	int dx, dy, steps, i;
	float xInc, yIntc, x = Begin.x, y = Begin.y;
	dx = end.x - Begin.x;
	dy = end.y - Begin.y;
	if (fabs(dx)>fabs(dy))
	{
		steps = fabs(dx);
	}
	else
	{
		steps = fabs(dy);
	}
	buffer.DrawPixel(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5),LineColor);
	xInc = (float)dx / (float)steps;
	yIntc = (float)dy / (float)steps;
	for (int i = 0; i < steps; i++)
	{
		x += xInc;
		y += yIntc;

		buffer.DrawPixel(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5),LineColor);
	}

}
//Bresenham算法是一个只用正数增量进行计算，精确并且有效的光栅化生成算法
void ImageInstance::DrawBresenhamLine(vector2i Begin, vector2i end, Color LineColor)
{
	int x0 =Begin.x;
	int x1 = end.x;
	int y0 = Begin.y;
	int y1 = end.y;
	bool steep = false;
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int k = dy > 0 ? 1 : -1;
	if (dy < 0)dy = -dy;
	float e = -dx;
	int x = x0, y = y0;
	while (x != x1)
	{
		if (steep)
		{
			buffer.DrawPixel(y, x,LineColor);
		}
		else
		{
			buffer.DrawPixel(x, y, LineColor);
		}
		e += (2 * dy);
		if (e > 0)
		{
			y += k;
			e -= (2 * dx);
		}
		++x;
	}
}

void ImageInstance::DrawBresenhamLine(vector3f Begin, vector3f end, Color LineColor)
{
	int x0 = ToInt(Begin.x);
	int x1 = ToInt(end.x);
	int y0 = ToInt(Begin.y);
	int y1 = ToInt(end.y);
	bool steep = false;
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int k = dy > 0 ? 1 : -1;
	if (dy < 0)dy = -dy;
	float e = -dx;
	int x = x0, y = y0;
	while (x != x1)
	{
		if (steep)
		{
			buffer.DrawPixel(y, x, LineColor);
		}
		else
		{
			buffer.DrawPixel(x, y, LineColor);
		}
		e += (2 * dy);
		if (e > 0)
		{
			y += k;
			e -= (2 * dx);
		}
		++x;
	}
}

ImageInstance& ImageInstance::GetInstance()
{
	static ImageInstance Instance;
	return Instance;
}

void ImageInstance::ClearImage()
{
	buffer.ClearImage();
	buffer.ResetDepth();
}

void ImageInstance::FillImage()
{
	buffer.FillColor();
}

std::vector<vector3f> ImageInstance::UpdateViewPlanes( Matrix& vp)
{
	vector<vector3f> planes(6, vector3f());
	//左侧  
	planes[0].x = vp.GetItemByindex(0, 3) + vp.GetItemByindex(0, 0);
	planes[0].y = vp.GetItemByindex(1, 3) + vp.GetItemByindex(1, 0);
	planes[0].z = vp.GetItemByindex(2, 3) + vp.GetItemByindex(2, 0);
	planes[0].w = vp.GetItemByindex(3, 3) + vp.GetItemByindex(3, 0);
	//右侧
	planes[1].x = vp.GetItemByindex(0, 3) - vp.GetItemByindex(0, 0);
	planes[1].y = vp.GetItemByindex(1, 3) - vp.GetItemByindex(1, 0);
	planes[1].z = vp.GetItemByindex(2, 3) - vp.GetItemByindex(2, 0);
	planes[1].w = vp.GetItemByindex(3, 3) - vp.GetItemByindex(3, 0);
	//上侧
	planes[2].x = vp.GetItemByindex(0, 3) - vp.GetItemByindex(0, 1);
	planes[2].y = vp.GetItemByindex(1, 3) - vp.GetItemByindex(1, 1);
	planes[2].z = vp.GetItemByindex(2, 3) - vp.GetItemByindex(2, 1);
	planes[2].w = vp.GetItemByindex(3, 3) - vp.GetItemByindex(3, 1);
	//下侧
	planes[3].x = vp.GetItemByindex(0, 3) + vp.GetItemByindex(0, 1);
	planes[3].y = vp.GetItemByindex(1, 3) + vp.GetItemByindex(1, 1);
	planes[3].z = vp.GetItemByindex(2, 3) + vp.GetItemByindex(2, 1);
	planes[3].w = vp.GetItemByindex(3, 3) + vp.GetItemByindex(3, 1);
	//Near
	planes[4].x = vp.GetItemByindex(0, 3) + vp.GetItemByindex(0, 2);
	planes[4].y = vp.GetItemByindex(1, 3) + vp.GetItemByindex(1, 2);
	planes[4].z = vp.GetItemByindex(2, 3) + vp.GetItemByindex(2, 2);
	planes[4].w = vp.GetItemByindex(3, 3) + vp.GetItemByindex(3, 2);
	//Far
	planes[5].x = vp.GetItemByindex(0, 3) - vp.GetItemByindex(0, 2);
	planes[5].y = vp.GetItemByindex(1, 3) - vp.GetItemByindex(1, 2);
	planes[5].z = vp.GetItemByindex(2, 3) - vp.GetItemByindex(2, 2);
	planes[5].w = vp.GetItemByindex(3, 3) - vp.GetItemByindex(3, 2);

	return planes;

}

bool ImageInstance::ViewCull(const vector3f& p1, const vector3f& p2, const vector3f& p3,  VertexShader& vsShader)
{
	Matrix vp = vsShader.projection * vsShader.view;
	vector<vector3f>ViewPlanes = UpdateViewPlanes(vp);
	vector3f minPoint, maxPoint;
	minPoint.x = min(p1.x, min(p2.x, p3.x));
	minPoint.y = min(p1.y, min(p2.y, p3.y));
	minPoint.z = min(p1.z, min(p2.z, p3.z));
	maxPoint.x = max(p1.x, max(p2.x, p3.x));
	maxPoint.y = max(p1.y, max(p2.y, p3.y));
	maxPoint.z = max(p1.z, max(p2.z, p3.z));
	if (!PointToPlane(minPoint, ViewPlanes[4]) || !PointToPlane(maxPoint, ViewPlanes[4]))
	{
		return false;
	}
	if (!PointToPlane(minPoint, ViewPlanes[5]) || !PointToPlane(maxPoint, ViewPlanes[5]))
	{
		return false;
	}
	if (!PointToPlane(minPoint, ViewPlanes[0]) || !PointToPlane(maxPoint, ViewPlanes[0]))
	{
		return false;
	}
	if (!PointToPlane(minPoint, ViewPlanes[1]) || !PointToPlane(maxPoint, ViewPlanes[1]))
	{
		return false;
	}
	if (!PointToPlane(minPoint, ViewPlanes[2]) || !PointToPlane(maxPoint, ViewPlanes[2]))
	{
		return false;
	}
	if (!PointToPlane(minPoint, ViewPlanes[3]) || !PointToPlane(maxPoint, ViewPlanes[3]))
	{
		return false;
	}
	return true;

}

vector<vector2i> ImageInstance::CreateBoundBox(vector<vector3f> t)
{
	int xMin = Default_Width - 1;
	int yMin = Default_Height - 1;
	int xMax = 0;
	int yMax = 0;
	for (int i = 0; i < 3; i++)
	{
		xMin = min(xMin, t[i].x);
		yMin = min(yMin, t[i].y);
		xMax = max(xMax, t[i].x);
		yMax = max(yMax, t[i].y);
	}
	xMin = xMin > 0 ? xMin : 0;
	yMin = yMin > 0 ? yMin : 0;
	xMax = yMax < Default_Width - 1 ? xMax : Default_Width - 1;
	yMax = yMax < Default_Height - 1 ? yMax : Default_Height - 1;
	return{ {xMin,yMin},{xMax,yMax} };
}

void ImageInstance::DrawTriangle(vertex t0, vertex t1, vertex t2, FragmentShader* fsShader)
{
	FragmentItem Item;
	vector<vector3f> res{ t0.ScreenSpacePostionNoFilp,t1.ScreenSpacePostionNoFilp,t2.ScreenSpacePostionNoFilp };
	
	vector2i box_min = vector2{ ToInt(CreateBoundBox(res)[0].x),ToInt(CreateBoundBox(res)[0].y) };
	vector2i box_max = vector2{ ToInt(CreateBoundBox(res)[1].x),ToInt(CreateBoundBox(res)[1].y) };
	vector3f p;
	vertex test[3] = { t0,t1,t2 };
	for (p.x = box_min.x; p.x < box_max.x; p.x++)
	{
		for (p.y = box_min.y; p.y < box_max.y; p.y++)
		{
			vector3f bc_screen = CenterOfGravity3D(res[0], res[1], res[2], p);
			float bc[3] = { bc_screen.x,bc_screen.y,bc_screen.z };
			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0)
			{
				continue;
			}
			p.z = 0;
			for (int i = 0; i < 3; i++)
			{
				p.z += res[i].z * bc[i];//重心坐标做插值
			}
			if (buffer.JudgeDepth(int(p.x), int(p.y), p.z))
			{
				

				Item.texCoord = CalculateInterpolation(t0.uv,t1.uv,t2.uv,bc_screen);
				Item.FragPosition = CalculateInterpolation(t0.WorldSpacePosition, t1.WorldSpacePosition, t2.WorldSpacePosition, bc_screen);
				Item.Normal = CalculateInterpolation(t0.Normal, t1.Normal, t2.Normal, bc_screen);
				
				Color TriangeleColor= fsShader->CalculateColor(Item);
				buffer.UpdateColor(int(p.x), int(p.y), TriangeleColor);

			}



		}

	}
}

void ImageInstance::DrawTriangle(vector2i t0, vector2i t1, vector2i t2, Color TriangeleColor)
{
	//创建包围盒
	vector<vector3f> res{ {float(t0.x),float(t0.y),1.0},{float(t1.x),float(t1.y),1.0},{float(t2.x),float(t2.y),1.0} };


	vector2i box_min = vector2{ CreateBoundBox(res)[0].x,CreateBoundBox(res)[0].y };
	vector2i box_max = vector2{ CreateBoundBox(res)[1].x,CreateBoundBox(res)[1].y };
	vector2i p;
	for (p.x=box_min.x;p.x<box_max.x;p.x++)
	{
		for (p.y=box_min.y;p.y<box_max.y;p.y++)
		{
			vector3f bc_screen = CenterOfGravity2D(t0, t1, t2, p);
			if (bc_screen.x<0||bc_screen.y<0||bc_screen.z<0)
			{
				continue;
			}
			buffer.DrawPixel(p.x, p.y, TriangeleColor);
		}

	}
}

void ImageInstance::DrawTriangle(vector3f t0, vector3f t1, vector3f t2, Color TriangeleColor)
{

	//todo背面剔除
	

	vector<vector3f> res{ t0,t1,t2 };
	vector2i box_min = vector2{ ToInt(CreateBoundBox(res)[0].x),ToInt(CreateBoundBox(res)[0].y) };
	vector2i box_max = vector2{ToInt(CreateBoundBox(res)[1].x),ToInt(CreateBoundBox(res)[1].y )};

	vector3f p;
	for (p.x = box_min.x; p.x < box_max.x; p.x++)
	{
		for (p.y = box_min.y; p.y < box_max.y; p.y++)
		{
			vector3f bc_screen = CenterOfGravity3D(t0, t1, t2, p);
			float bc[3] = { bc_screen.x,bc_screen.y,bc_screen.z };
			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0)
			{
				continue;
			}
			p.z = 0;
			for (int i = 0; i < 3; i++)
			{
				p.z += res[i].z * bc[i];//重心坐标做插值
			}
			
			if (buffer.JudgeDepth(int(p.x),int(p.y),p.z))
			{
				//buffer.DrawPixel(int(p.x), int(p.y), TriangeleColor);
				buffer.UpdateColor(int(p.x), int(p.y), TriangeleColor);

			}

		}

	}
}

void ImageInstance::DrawWireframeModel(LoadModel* model)
{
	for (int i = 0; i < model->nfaces(); i++) 
	{
		std::vector<int> face = model->face(i);
		for (int j = 0; j < 3; j++) {
			vector3f v0(model->vert(face[j]).x, model->vert(face[j]).y, model->vert(face[j]).z);
			vector3f v1(model->vert(face[(j + 1) % 3]).x, model->vert(face[(j + 1) % 3]).y, model->vert(face[(j + 1) % 3]).z);
			int x0 = (v0.x + 1.) * Default_Width / 2.;
			int y0 = (v0.y + 1.) * Default_Height / 2.;
			int x1 = (v1.x + 1.) * Default_Width / 2.;
			int y1 = (v1.y + 1.) * Default_Height / 2.;
			DrawBresenhamLine(vector2(x0,  Default_Height-y0), vector2(x1, Default_Height- y1), Color());


		}
	}
}

void ImageInstance::DrawWireframeModel(LoadModel* model, VertexShader& vsShader)
{
	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int>face = model->face(i);
		vertex Vertexs[3];
		for (int j = 0; j < 3; j++)
		{
			Vertexs[j] = model->vt_vert(face[j]);
			Vertexs[j].CalculateMatrix(vsShader.view, vsShader.model, vsShader.projection, vsShader.viewport);
		}

		//视锥体剔除
		if (!ViewCull(Vertexs[0].WorldSpacePosition, Vertexs[1].WorldSpacePosition, Vertexs[2].WorldSpacePosition, vsShader))
		{
			//continue;
		}

		// //判断是否整个三角形是否在NDC里面，如果没有，需要进行裁切
		//https://zhuanlan.zhihu.com/p/97371838
		if (AllVertexInside(Vertexs[0].NDCSpacePosition, Vertexs[1].NDCSpacePosition, Vertexs[2].NDCSpacePosition))
		{
			DrawBresenhamLine(Vertexs[0].ScreenSpacePostion, Vertexs[1].ScreenSpacePostion,Color());
			DrawBresenhamLine(Vertexs[1].ScreenSpacePostion, Vertexs[2].ScreenSpacePostion, Color());
			DrawBresenhamLine(Vertexs[2].ScreenSpacePostion, Vertexs[0].ScreenSpacePostion, Color());
		}
		else
		{
			vector<vector3f> NewVertexs = ViewportCulling(Vertexs[0].NDCSpacePosition, Vertexs[1].NDCSpacePosition, Vertexs[2].NDCSpacePosition);
			int TriangleNum = NewVertexs.size() - 2;
			for (int i = 0; i < TriangleNum; i++)
			{
				//需要把新顶点的UV，屏幕坐标求出来放进新构造的vertex中
				vertex NewVertex[3];

				NewVertex[0].NDCSpacePosition = NewVertexs[0];
				NewVertex[1].NDCSpacePosition = NewVertexs[i + 1];
				NewVertex[2].NDCSpacePosition = NewVertexs[i + 2];
				for (int j = 0; j < 3; j++)
				{
					NewVertex[j].CalculateMatrix(vsShader.viewport);
					vector3f bc_screen = CenterOfGravity3D(Vertexs[0].ScreenSpacePostionNoFilp, Vertexs[1].ScreenSpacePostionNoFilp, Vertexs[2].ScreenSpacePostionNoFilp, NewVertex[j].ScreenSpacePostionNoFilp);
					NewVertex[j].uv = CalculateInterpolation(Vertexs[0].uv, Vertexs[1].uv, Vertexs[2].uv, bc_screen);
					NewVertex[j].Normal = Vertexs[0].Normal;
				}
				DrawBresenhamLine(NewVertex[0].ScreenSpacePostion, NewVertex[1].ScreenSpacePostion, Color());
				DrawBresenhamLine(NewVertex[1].ScreenSpacePostion, NewVertex[2].ScreenSpacePostion, Color());
				DrawBresenhamLine(NewVertex[2].ScreenSpacePostion, NewVertex[0].ScreenSpacePostion, Color());
			}
		}

	}
}

void ImageInstance::DrawPureModel(LoadModel* model)
{
	for (int i = 0; i < model->nfaces(); i++) 
	{
		std::vector<int> face = model->face(i);
		vector2i screen_coords[3];


		for (int j = 0; j < 3; j++) 
		{
			vector3f world_coords = model->vert(face[j]);
			screen_coords[j] = vector2i((world_coords.x + 1.) * Default_Width / 2., (1.0-world_coords.y ) * Default_Height / 2.);
			
		}
		DrawTriangle(vector2i(screen_coords[0].x,screen_coords[0].y), vector2i(screen_coords[1].x,screen_coords[1].y), vector2i(screen_coords[2].x, screen_coords[2].y),Color(rand() % 255, rand() % 255, rand() % 255));
		
	}
}

void ImageInstance::DrawModelWIthBaseLighting(LoadModel* model)
{
	vector3f LightingDir = vector3f(0, 0, -1.f);
	for (int i=0;i<model->nfaces();i++)
	{
		vector<int> face = model->face(i);
		vector3f worldCoord[3];
		vector2i screenCoord[3];
		for (int j = 0; j < 3; j++)
		{
			worldCoord[j] = model->vert(face[j]);
			screenCoord[j] = vector2i((worldCoord[j].x + 1.) * Default_Width / 2., (1.0-worldCoord[j].y ) * Default_Height / 2.);
		}
		//求法线
		vector3f nor = vector3<float>::Cross(worldCoord[2] - worldCoord[0], worldCoord[1] - worldCoord[0]);
		nor.Normalize();
		float intensity = LightingDir.dot(nor);
		if (intensity>0)
		{
			DrawTriangle(vector2i(screenCoord[0].x, screenCoord[0].y), vector2i(screenCoord[1].x,  screenCoord[1].y), vector2i(screenCoord[2].x,  screenCoord[2].y), Color(intensity, intensity , intensity));
	
		}

	}
}

void ImageInstance::DrawModelWithZBuffer(LoadModel* model)
{
	buffer.ResetDepth();
	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		vector3f screenCoord[3];
		for (int j = 0; j < 3; j++)
		{
			vector3f temp = model->vert(face[j]);
			screenCoord[j] = vector3f(int(((temp.x + 1.f) * Default_Width / 2.0f) + 0.5f), int(((1.-temp.y) * Default_Height / 2.0f) + 0.5f), temp.z);
		}
		DrawTriangle(screenCoord[0], screenCoord[1], screenCoord[2], Color(rand() % 255, rand() % 255, rand() % 255));
	}
}


void ImageInstance::DrawModelWithVertex(LoadModel* model, VertexShader& vsShader)
{

	vector3f LightingPos = vector3f(0, 0, -1.f);
	buffer.ResetDepth();
	buffer.ClearImage();

	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int>face = model->face(i);
		vector3f worldCoord[3];
		vector3f screenCoord[3];
		for (int j=0;j<3;j++)
		{
			vertex Temp = model->vt_vert(face[j]);
			
			
			screenCoord[j] = Temp.CalculateMatrix(vsShader.view, vsShader.model, vsShader.projection, vsShader.viewport);
			worldCoord[j] = Temp.WorldSpacePosition;
			
		}
		vector3f nor = vector3<float>::Cross(worldCoord[2] - worldCoord[0], worldCoord[1] - worldCoord[0]);
		nor.Normalize();
		float intensity = LightingPos.dot(nor);
		DrawTriangle(screenCoord[0],screenCoord[1],screenCoord[2], Color(intensity , intensity , intensity ));

		



	}
	buffer.FillColor();
	
}

void ImageInstance::DrawModelWithFragment(LoadModel* model, VertexShader& vsShader, FragmentShader* fsShader)
{

	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int>face = model->face(i);
		vertex Vertexs[3];
		for (int j = 0; j < 3; j++)
		{
			Vertexs[j] = model->vt_vert(face[j]);
			Vertexs[j].CalculateMatrix(vsShader.view,vsShader.model,vsShader.projection,vsShader.viewport);
		}

		//视锥体剔除
		if (!ViewCull(Vertexs[0].WorldSpacePosition , Vertexs[1].WorldSpacePosition , Vertexs[2].WorldSpacePosition ,vsShader))
		{
			//continue;
		}

		// //判断是否整个三角形是否在NDC里面，如果没有，需要进行裁切
		//https://zhuanlan.zhihu.com/p/97371838
		if (AllVertexInside(Vertexs[0].NDCSpacePosition, Vertexs[1].NDCSpacePosition, Vertexs[2].NDCSpacePosition))
		{
			DrawTriangle(Vertexs[0], Vertexs[1], Vertexs[2], fsShader);
		}
		else
		{
			vector<vector3f> NewVertexs = ViewportCulling(Vertexs[0].NDCSpacePosition, Vertexs[1].NDCSpacePosition, Vertexs[2].NDCSpacePosition);
			int TriangleNum = NewVertexs.size() - 2;
			for (int i = 0; i < TriangleNum; i++)
			{
				//需要把新顶点的UV，屏幕坐标求出来放进新构造的vertex中
				vertex NewVertex[3];

				NewVertex[0].NDCSpacePosition = NewVertexs[0];
				NewVertex[1].NDCSpacePosition = NewVertexs[i+1];
				NewVertex[2].NDCSpacePosition = NewVertexs[i+2];
				for (int j = 0; j < 3; j++)
				{
					NewVertex[j].CalculateMatrix(vsShader.viewport);
					vector3f bc_screen = CenterOfGravity3D(Vertexs[0].ScreenSpacePostionNoFilp, Vertexs[1].ScreenSpacePostionNoFilp, Vertexs[2].ScreenSpacePostionNoFilp, NewVertex[j].ScreenSpacePostionNoFilp);
					NewVertex[j].uv= CalculateInterpolation(Vertexs[0].uv, Vertexs[1].uv, Vertexs[2].uv, bc_screen);
					NewVertex[j].Normal= Vertexs[0].Normal;
				}
				DrawTriangle(NewVertex[0], NewVertex[1], NewVertex[2], fsShader);
			}
		}
			
	}

}
