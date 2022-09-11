#include "CustomVertex.h"
#include "CustomMath.h"



vertex::vertex()
{

}

vertex::vertex(vector3f localpos, vector3f normal, vector2f uv_)
	:LocalObjectPosition(localpos),Normal(normal),uv(uv_)
{

}

vertex::vertex(vector3f localpos)
	: LocalObjectPosition(localpos)
{

}

vector3f vertex::CalculateMatrix(const Matrix& view, const Matrix& model, const Matrix& projection, const Matrix& viewport)
{
	WorldSpacePosition = model * LocalObjectPosition;

	ClipSpacePosition =projection * (view * (WorldSpacePosition));


	NDCSpacePosition = ToPoint( ClipSpacePosition);


	ScreenSpacePostionNoFilp =viewport*NDCSpacePosition;

	//���ǵ�Qt������������ԣ���Ҫ��תһ��y������
	ScreenSpacePostion = FilpHeight(ScreenSpacePostionNoFilp);

	ScreenDepth = ScreenSpacePostion.z;
	

	return ScreenSpacePostion;

}


vector3f vertex::CalculateMatrix(const Matrix& viewport)
{
	ScreenSpacePostionNoFilp = viewport * NDCSpacePosition;

	//���ǵ�Qt������������ԣ���Ҫ��תһ��y������
	ScreenSpacePostion = FilpHeight(ScreenSpacePostionNoFilp);

	ScreenDepth = ScreenSpacePostion.z;


	return ScreenSpacePostion;
}

//vector3f vertex::CalculateMatrix( VertexShader& shader)
//{
//	WorldSpacePosition = shader.model * LocalObjectPosition;
//
//	ClipSpacePosition = shader.projection * (shader.view * (WorldSpacePosition));
//
//
//	NDCSpacePosition = ToPoint(ClipSpacePosition);
//
//	ScreenSpacePostionNoFilp = shader.viewport * NDCSpacePosition;
//
//	//���ǵ�Qt������������ԣ���Ҫ��תһ��y������
//	ScreenSpacePostion = FilpHeight(ScreenSpacePostionNoFilp);
//
//	ScreenDepth = ScreenSpacePostion.z;
//
//
//	return ScreenSpacePostion;
//}
