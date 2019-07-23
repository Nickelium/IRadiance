#pragma once

#include "Vector.h"

namespace IRadiance
{
	class Vector;

	class Point
	{
	public:
		float x, y, z;

		Point(float _val = 0.0f);
		Point(float _x, float _y, float _z);
		Point(const Point& _other);
		Point(const Vector& _v);

		Point& operator=(const Point& _other);

		Point& operator+=(const Vector& _v);
		Point& operator-=(const Vector& _v);
		Point& operator*=(float _f);
	};

	Point operator+(const Point& _p);
	Point operator-(const Point& _p);

	Point operator+(const Point& _p, const Vector& _v);
	Point operator-(const Point& _p, const Vector& _v);
	Vector operator-(const Point& _p1, const Point& _p2);

	Point operator*(const Point& _p, float _f);
	Point operator*(float _f, const Point& _p);
}
