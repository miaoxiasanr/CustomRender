#ifndef LOADMODEL_H
#define LOADMODEL_H

#include <vector>
#include "CustomVertex.h"
#include "CustomVector.h"
class LoadModel
{
public:
	LoadModel(const char* filename);
	LoadModel(vector<vector3f>verts, vector<vector<int>>faces, vector<vector2f>uv,vector<vector3f>normals);
	~LoadModel() {};
	int nverts();
	int nfaces();
	vector<int>face(int index);
	vector3f vert(int index);
	vertex vt_vert(int index);
	vector3f normal(int index);
	vector2f GetUV(int index);

private:
	vector<vector3f>verts_;
	vector<vector<int>> faces_;
	vector<vertex>vt_verts_;
	vector<vector3f>normal_;
	vector<vector2f>uv_;
};

#endif

