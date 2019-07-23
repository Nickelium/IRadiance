#include "pch.h"
#include "Point.h"

#include "Vector.h"

namespace IRadiance
{
	Point::Point(float _val /*= 0.0f*/)
		: Point(_val, _val, _val)
	{
	}

	Point::Point(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{
	}

	Point::Point(const Point& _other)
		: Point(_other.x, _other.y, _other.z)
	{
	}

	Point::Point(const Vector& _v)
		: Point(_v.x, _v.y, _v.z)
	{

	}

	Point& Point::operator*=(float _f)
	{
		x *= _f;
		y *= _f;
		z *= _f;
		return *this;
	}

	Point& Point::operator-=(const Vector& _v)
	{
		x -= _v.x;
		y -= _v.y;
		z -= _v.z;
		return *this;
	}

	Point& Point::operator+=(const Vector& _v)
	{
		x += _v.x;
		y += _v.y;
		z += _v.z;
		return *this;
	}

	Point& Point::operator=(const Point& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		return *this;
	}

	Point operator+(const Point& _p)
	{
		return _p;
	}

	Point operator-(const Point& _p)
	{
		Point p;
		p.x = -_p.x;
		p.y = -_p.y;
		p.z = -_p.z;
		return p;
	}
		
	Point operator+(const Point& _p, const Vector& _v)
	{
		Point p;
		p.x = _p.x + _v.x;
		p.y = _p.y + _v.y;
		p.z = _p.z + _v.z;
		return p;
	}


	Point operator-(const Point& _p, const Vector& _v)
	{
		Point p;
		p.x = _p.x - _v.x;
		p.y = _p.y - _v.y;
		p.z = _p.z - _v.z;
		return p;
	}

	Vector operator-(const Point& _p1, const Point& _p2)
	{
		Vector v;;
		v.x = _p1.x - _p2.x;
		v.y = _p1.y - _p2.y;
		v.z = _p1.z - _p2.z;
		return v;

	}

	Point operator*(const Point& _p, float _f)
	{
		Point p;
		p.x = _p.x * _f;
		p.y = _p.y * _f;
		p.z = _p.z * _f;
		return p;
	}

	Point operator*(float _f, const Point& _p)
	{
		return _p * _f;
	}
}