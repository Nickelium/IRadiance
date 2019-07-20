#pragma once

namespace IRadiance
{
	class Vector;
	class Point;

	class Normal
	{
	public:
		float x, y, z;
	
		Normal(float _val = 0.0f);
		Normal(float _x, float _y, float _z);
		Normal(const Normal& _other);
		Normal(const Vector& _v);
		Normal(const Point& _p);
	
		Normal& operator=(const Normal& _other);
		Normal& operator=(const Vector& _v);
		Normal& operator=(const Point& _p);
		
		Normal& operator+=(const Normal& _n);
		Normal& operator-=(const Normal& _n);
		Normal& operator*=(float _f);
	
		Normal& Normalize();
	};
	
	Normal operator+(const Normal& _n);
	Normal operator-(const Normal& _n);
	
	Normal operator+(const Normal& _n1, const Normal& _n2);
	Normal operator-(const Normal& _n1, const Normal& _n2);
	Normal operator*(const Normal& _n, float _f);
	Normal operator*(float _f, const Normal& _n);
	
	//TODO Completed API as Vector and between vector and normals
}
