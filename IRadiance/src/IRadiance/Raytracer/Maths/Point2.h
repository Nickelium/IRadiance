#pragma once

#include "Vector.h"

namespace IRadiance
{
	class Vector;

	class Point2
	{
	public:
		float x, y;

		Point2(float _val = 0.0f);
		Point2(float _x, float _y);
		Point2(const Point2& _other);
		Point2(const Point3& _p);

		Point2& operator=(const Point2& _other);

		Point2& operator*=(float _f);
	};

	Point2 operator+(const Point2& _p);
	Point2 operator-(const Point2& _p);

	Vector operator-(const Point2& _p1, const Point2& _p2);

	Point2 operator*(const Point2& _p, float _f);
	Point2 operator*(float _f, const Point2& _p);
}
