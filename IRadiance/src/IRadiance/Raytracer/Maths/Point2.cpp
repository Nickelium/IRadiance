#include "pch.h"
#include "Point2.h"

#include "Point3.h"

namespace IRadiance
{
	Point2::Point2(float _val /*= 0.0f*/)
		: Point2(_val, _val)
	{
	}

	Point2::Point2(float _x, float _y)
		: x(_x), y(_y)
	{
	}

	Point2::Point2(const Point2& _other)
		: Point2(_other.x, _other.y)
	{
	}

	Point2::Point2(const Point3& _p)
		: Point2(_p.x, _p.y)
	{
	}

	Point2& Point2::operator*=(float _f)
	{
		x *= _f;
		y *= _f;
		return *this;
	}

	Point2& Point2::operator=(const Point2& _other)
	{
		x = _other.x;
		y = _other.y;
		return *this;
	}

	Point2 operator+(const Point2& _p)
	{
		return _p;
	}

	Point2 operator-(const Point2& _p)
	{
		Point2 p;
		p.x = -_p.x;
		p.y = -_p.y;
		return p;
	}

	Vector operator-(const Point2& _p1, const Point2& _p2)
	{
		Vector v;;
		v.x = _p1.x - _p2.x;
		v.y = _p1.y - _p2.y;
		return v;

	}

	Point2 operator*(const Point2& _p, float _f)
	{
		Point2 p;
		p.x = _p.x * _f;
		p.y = _p.y * _f;
		return p;
	}

	Point2 operator*(float _f, const Point2& _p)
	{
		return _p * _f;
	}
}