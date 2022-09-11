#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H
#include "CustomMatrix.h"
#include "Configure.h"
#include "CustomMath.h"
class VertexShader
{
public:
	Matrix model;
	Matrix view;
	Matrix projection;
	Matrix viewport;
public:
	VertexShader();
	VertexShader(Matrix model_,Matrix view_,Matrix projection_,Matrix viewport_);
};
#endif

