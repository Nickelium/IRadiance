#pragma once

#include "Vector.h"

namespace IRadiance
{
	class Vector;

	class Point3
	{
	public:
		float x, y, z;

		Point3(float _val = 0.0f);
		Point3(float _x, float _y, float _z);
		Point3(const Point3& _other);
		Point3(const Vector& _v);

		Point3& operator=(const Point3& _other);

		Point3& operator+=(const Vector& _v);
		Point3& operator-=(const Vector& _v);
		Point3& operator*=(float _f);
	};

	Point3 operator+(const Point3& _p);
	Point3 operator-(const Point3& _p);

	Point3 operator+(const Point3& _p, const Vector& _v);
	Point3 operator-(const Point3& _p, const Vector& _v);
	Vector operator-(const Point3& _p1, const Point3& _p2);

	Point3 operator*(const Point3& _p, float _f);
	Point3 operator*(float _f, const Point3& _p);
}
