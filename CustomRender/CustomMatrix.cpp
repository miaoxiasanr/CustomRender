#include "CustomMatrix.h"

Matrix::Matrix()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			value[i][j] = 0.f;
		}
	}
}


Matrix::~Matrix()
{

}

Matrix Matrix::operator+(const Matrix& Right) const
{
	Matrix m;
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			m.value[i][j] = value[i][j] + Right.value[i][j];
		}
	}
	return m;
}

Matrix Matrix::operator-(const Matrix& Right) const
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.value[i][j] = value[i][j] - Right.value[i][j];
		}
	}
	return m;
}

Matrix Matrix::operator*(const Matrix& Right) const
{
	vector3f ScrA0 = (*this)[0];
	vector3f ScrA1 = (*this)[1];
	vector3f ScrA2 = (*this)[2];
	vector3f ScrA3 = (*this)[3];

	vector3f ScrB0 = Right[0];
	vector3f ScrB1 = Right[1];
	vector3f ScrB2 = Right[2];
	vector3f ScrB3 = Right[3];

	Matrix m;
	m.uninitialize();
	m.SetMatrixByindex(0, ScrA0 * ScrB0.x + ScrA1 * ScrB0.y + ScrA2 * ScrB0.z + ScrA3 * ScrB0.w);
	m.SetMatrixByindex(1, ScrA0 * ScrB1.x + ScrA1 * ScrB1.y + ScrA2 * ScrB1.z + ScrA3 * ScrB1.w);
	m.SetMatrixByindex(2, ScrA0 * ScrB2.x + ScrA1 * ScrB2.y + ScrA2 * ScrB2.z + ScrA3 * ScrB2.w);
	m.SetMatrixByindex(3, ScrA0 * ScrB3.x + ScrA1 * ScrB3.y + ScrA2 * ScrB3.z + ScrA3 * ScrB3.w);
	return m;
}

Matrix Matrix::operator*(const float& Right) const
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.value[i][j] = value[i][j] * Right;

		}
	}
	return m;
}

vector3f Matrix::operator*(const vector3f& v) const
{
	float valueX = v.x * value[0][0] + v.y * value[0][1] + v.z * value[0][2] + v.w * value[0][3];
	float valueY = v.x * value[1][0] + v.y * value[1][1] + v.z * value[1][2] + v.w * value[1][3];
	float valueZ = v.x * value[2][0] + v.y * value[2][1] + v.z * value[2][2] + v.w * value[2][3];
	float valueW = v.x * value[3][0] + v.y * value[3][1] + v.z * value[3][2] + v.w * value[3][3];
	return vector3<float>(valueX, valueY, valueZ, valueW);
}

vector3f Matrix::operator[](const int Right) const
{
	return vector3f(value[Right][0], value[Right][1], value[Right][2], value[Right][3]);
}

void Matrix::Identity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i==j)
			{
				value[i][j] = 1;
			}
			else
			{
				value[i][j] = 0;
			}

		}
	}
}

void Matrix::uninitialize()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			value[i][j] = 0.f;
		}
	}
}

void Matrix::SetMatrixByindex(const int index, const vector3f& v)
{
	value[index][0] = v.x;
	value[index][1] = v.y;
	value[index][2] = v.z;
	value[index][3] = v.w;
}

float Matrix::GetItemByindex(const int& Row, const int& Column)
{
	return value[Row][Column];
}

vector3<float> Matrix::MultiplyVector3(const vector3<float>& v) const
{
	float valueX = v.x * value[0][0] + v.y * value[0][1] + v.z * value[0][2] + v.w * value[0][3];
	float valueY = v.x * value[1][0] + v.y * value[1][1] + v.z * value[1][2] + v.w * value[1][3];
	float valueZ = v.x * value[2][0] + v.y * value[2][1] + v.z * value[2][2] + v.w * value[2][3];
	float valueW = v.x * value[3][0] + v.y * value[3][1] + v.z * value[3][2] + v.w * value[3][3];
	return vector3<float>(valueX, valueY, valueZ, valueW);
}

Matrix Matrix::Transpose() const
{
	Matrix ans;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ans.value[i][j] = value[j][i];
		}
	}
	return ans;
}

void Matrix::DeBug()
{
	cout << "-----------------Matrix Begin--------------" << endl;
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			cout << value[i][j] << "   ";
		}
		cout << endl;
	}
	cout << "-----------------Matrix End--------------" << endl;
}
