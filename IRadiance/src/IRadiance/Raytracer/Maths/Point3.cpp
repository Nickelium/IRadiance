#include "pch.h"
#include "Point3.h"

#include "Vector.h"

namespace IRadiance
{
	Point3::Point3(float _val /*= 0.0f*/)
		: Point3(_val, _val, _val)
	{
	}

	Point3::Point3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{
	}

	Point3::Point3(const Point3& _other)
		: Point3(_other.x, _other.y, _other.z)
	{
	}

	Point3::Point3(const Vector& _v)
		: Point3(_v.x, _v.y, _v.z)
	{

	}

	Point3& Point3::operator*=(float _f)
	{
		x *= _f;
		y *= _f;
		z *= _f;
		return *this;
	}

	Point3& Point3::operator-=(const Vector& _v)
	{
		x -= _v.x;
		y -= _v.y;
		z -= _v.z;
		return *this;
	}

	Point3& Point3::operator+=(const Vector& _v)
	{
		x += _v.x;
		y += _v.y;
		z += _v.z;
		return *this;
	}

	Point3& Point3::operator=(const Point3& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		return *this;
	}

	Point3 operator+(const Point3& _p)
	{
		return _p;
	}

	Point3 operator-(const Point3& _p)
	{
		Point3 p;
		p.x = -_p.x;
		p.y = -_p.y;
		p.z = -_p.z;
		return p;
	}
		
	Point3 operator+(const Point3& _p, const Vector& _v)
	{
		Point3 p;
		p.x = _p.x + _v.x;
		p.y = _p.y + _v.y;
		p.z = _p.z + _v.z;
		return p;
	}


	Point3 operator-(const Point3& _p, const Vector& _v)
	{
		Point3 p;
		p.x = _p.x - _v.x;
		p.y = _p.y - _v.y;
		p.z = _p.z - _v.z;
		return p;
	}

	Vector operator-(const Point3& _p1, const Point3& _p2)
	{
		Vector v;;
		v.x = _p1.x - _p2.x;
		v.y = _p1.y - _p2.y;
		v.z = _p1.z - _p2.z;
		return v;

	}

	Point3 operator*(const Point3& _p, float _f)
	{
		Point3 p;
		p.x = _p.x * _f;
		p.y = _p.y * _f;
		p.z = _p.z * _f;
		return p;
	}

	Point3 operator*(float _f, const Point3& _p)
	{
		return _p * _f;
	}
}