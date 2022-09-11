#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H
#include "CustomVector.h"
#include "iostream"
using namespace std;
class Matrix
{
public:
	float value[4][4];
public:
	Matrix();

	~Matrix();
	Matrix operator+(const Matrix& Right)const;
	Matrix operator-(const Matrix& Right)const;
	Matrix operator*(const Matrix& Right)const;
	Matrix operator*(const float& Right)const;
	vector3f operator*(const vector3f& v)const;
	vector3f operator[](const int Right)const;
	
	

	void Identity();
	void uninitialize();
	void SetMatrixByindex(const int index, const vector3f& v);
	float GetItemByindex(const int& Row, const int& Column);
	vector3<float> MultiplyVector3(const vector3<float>&v)const;
	Matrix Transpose()const;
	void DeBug();

};

#endif

