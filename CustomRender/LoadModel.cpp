#include "LoadModel.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>



LoadModel::LoadModel(const char* filename)
{
	std::ifstream in;
	in.open(filename, std::ifstream::in);
	if (in.fail()) return;
	std::string line;
	while (!in.eof()) {
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v ")) {
			iss >> trash;
			float v[3];
			for (int i = 0; i < 3; i++)
			{
				iss >> v[i];
			}
			verts_.push_back({ v[0],v[1],v[2] });
			vt_verts_.push_back(vertex({ v[0],v[1],v[2] }));
		}
		else if (!line.compare(0, 2, "f ")) 
		{
			std::vector<int> f;
			int itrash, idx;
			iss >> trash;
			while (iss >> idx >> trash >> itrash >> trash >> itrash) {
				idx--; // in wavefront obj all indices start at 1, not zero
				f.push_back(idx);
			}
			faces_.push_back(f);
		}
		else if (!line.compare(0, 3, "vn "))
		{
			iss >> trash >> trash;
			float n[3];
			for (int i = 0; i < 3; i++)
			{
				iss >> n[i];
			}

			normal_.push_back({ n[0],n[1],n[2] });
		}
		else if (!line.compare(0, 3, "vt "))
		{
			iss >> trash >> trash;
			float uv[2];
			for (int i = 0; i < 2; i++)
			{
				iss >> uv[i];
			}
			uv_.push_back({uv[0],uv[1]});
		}
	}
	for (int i=0;i<normal_.size();i++)
	{
		vt_verts_[i].Normal = normal_[i];
	}
}

LoadModel::LoadModel(vector<vector3f>verts, vector<vector<int>>faces,vector<vector2f>uv,vector<vector3f>normals)
	:verts_(verts),faces_(faces),uv_(uv),normal_(normals)
{
	for (int i = 0; i < verts.size(); i++)
	{
		vertex tex(verts[i],normals[i],uv[i]);
		vt_verts_.push_back(tex);	
	}
}

int LoadModel::nverts()
{
	return verts_.size();
}

int LoadModel::nfaces()
{
	return faces_.size();
}

vector<int> LoadModel::face(int index)
{
	return faces_[index];
}

vector3f LoadModel::vert(int index)
{
	return verts_[index];
}

vertex LoadModel::vt_vert(int index)
{
	return vt_verts_[index];
}

vector3f LoadModel::normal(int index)
{
	return normal_[index];
}

vector2f LoadModel::GetUV(int index)
{
	return uv_[index];
}
