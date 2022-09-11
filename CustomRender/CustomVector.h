#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H
#pragma once
#include "iostream"
#include <windows.h>
using namespace std;
template<class T>
class vector2
{
public:
	vector2<T>();
	vector2<T>(T _x, T _y);
	~vector2<T>();

	vector2<T> operator+(const vector2& res)const;
	vector2<T> operator-(vector2& res);
	vector2<T> operator*(float& res);
	vector2<T> operator/(float& res);
public:
	T x;
	T y;

};

template<class T>
vector2<T> vector2<T>::operator+(const vector2& res) const
{
	return vector2<T>(res.x + x, res.y + y);
}



template<class T>
vector2<T> vector2<T>::operator/(float& res)
{
	return vector2<T>(x / res, y / res);
}

template<class T>
vector2<T> vector2<T>::operator*(float& res)
{
	return vector2<T>(x*res, y*res);
}



template<class T>
vector2<T>::~vector2()
{

}

template<class T>
vector2<T> vector2<T>::operator-(vector2& res)
{
	return vector2<T>(res.x-x,res.y-y);
}

template<class T>
vector2<T>::vector2(T _x, T _y)
	:x(_x),y(_y)
{

}

template<class T>
vector2<T>::vector2()
	:x(1.0),y(1.0)
{

}


using vector2i = vector2<int>;
using vector2f = vector2<float>;
template<class T>
class vector3
{
public:
	vector3<T>();
	vector3<T>(T _x, T _y, T _z);
	vector3<T>(T _x, T _y, T _z, T _w);



	vector3<T>operator+(const vector3<T>& res)const;
	vector3<T>operator*(const vector3<T>& res)const;
	vector3<T>operator-(const vector3<T>& res)const;
	vector3<T>operator*(const float& res)const;
	vector3<T>operator/(const float& res)const;
	template <class > friend std::ostream& operator<<(std::ostream& s, vector3<T>& v);

	float static  dot(const vector3<T>& v1, const vector3<T>&v2);
	float dot(const vector3<T>& v);

	vector3<T> static  Cross(const vector3<T>& v1, const vector3<T>& v2);

	vector3<T>Normalize();


	void DeBug();

public:

	T x, y, z, w;

};

template<class T>
vector3<T> vector3<T>::operator*(const vector3<T>& res) const
{
	return vector3<T>(x * res.x, y * res.y, z * res.z, w * res.w);
}


template <class t> std::ostream& operator<<(std::ostream& s, vector3<t>& v) {
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
	return s;
}


using vector3f=vector3<float>;
using vector3i = vector3<int>;

template<class T>
vector3<T>::vector3()
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}





template<class T>
vector3<T>::vector3(T _x, T _y, T _z)
	:x(_x),y(_y),z(_z),w(1)
{

}


template<class T>
vector3<T>::vector3(T _x, T _y, T _z, T _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

template<class T>
vector3<T> vector3<T>::operator/(const float& res) const
{
	vector3<T> returnvalue(x / res, y / res, z / res, w / res);
	return returnvalue;
}

template<class T>
float vector3<T>::dot(const vector3<T>& v1, const vector3<T>& v2)
{

	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}



template<class T>
float vector3<T>::dot(const vector3<T>& v)
{
	return x * v.x + y * v.y + z * v.z;
}

template<class T>
vector3<T> vector3<T>::Cross(const vector3<T>& v1, const vector3<T>& v2)
{
	float valueX = v1.y * v2.z - v1.z * v2.y;
	float valueY = v1.z * v2.x - v1.x * v2.z;
	float valueZ = v1.x * v2.y - v1.y * v2.x;
	return vector3<T>(valueX, valueY, valueZ);
}

template<class T>
vector3<T> vector3<T>::Normalize()
{

	/*UE里面的方法
	FORCEINLINE FVector FVector::GetSafeNormal(float Tolerance) const
{
	const float SquareSum = X*X + Y*Y + Z*Z;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if(SquareSum == 1.f)
	{
		return *this;
	}
	else if(SquareSum < Tolerance)
	{
		return FVector::ZeroVector;
	}
	const float Scale = FMath::InvSqrt(SquareSum);
	return FVector(X*Scale, Y*Scale, Z*Scale);
}
	*/
	float SquareSum = dot(*this, *this);
	float Magnitude = sqrt(SquareSum);
	*this = *this / Magnitude;
	return *this;
}

template<class T>
void vector3<T>::DeBug()
{
	cout << "x= " << x << endl;
	cout << "y= " << y << endl;
	cout << "z= " << z << endl;
	cout << "w= " << w << endl;
}

template<class T>
vector3<T> vector3<T>::operator*(const float& res) const
{
	vector3<T> returnvalue(x * res, y * res, z * res,w*res);
	return returnvalue;
}

template<class T>
vector3<T> vector3<T>::operator-(const vector3<T>& res) const
{
	vector3<T> returnvalue(x - res.x, y - res.y, z - res.z,w-res.w);
	return returnvalue;
}

template<class T>
vector3<T> vector3<T>::operator+(const vector3<T>& res) const
{
	vector3<T> returnvalue(x + res.x, y + res.y, z + res.z,w+res.w);
	return returnvalue;
}

#endif // 
