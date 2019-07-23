#include "pch.h"
#include "Normal.h"

#include "Vector.h"
#include "Point.h"

namespace IRadiance
{
	Normal::Normal(float _val /*= 0.0f*/)
		: Normal(_val, _val, _val)
	{
	}

	Normal::Normal(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{
	}

	Normal::Normal(const Normal& _other)
		: Normal(_other.x, _other.y, _other.z)
	{
	}

	Normal::Normal(const Vector& _v)
		: Normal(_v.x, _v.y, _v.z)
	{
	}

	Normal::Normal(const Point& _p)
		: Normal(_p.x, _p.y, _p.z)
	{
	}

	Normal& Normal::operator=(const Point& _p)
	{
		x = _p.x;
		y = _p.y;
		z = _p.z;
		return *this;
	}

	Normal& Normal::operator=(const Vector& _v)
	{
		x = _v.x;
		y = _v.y;
		z = _v.z;
		return *this;
	}

	Normal& Normal::Normalize()
	{

		return *this;
	}

	Normal& Normal::operator*=(float _f)
	{
		x *= _f;
		y *= _f;
		z *= _f;
		return *this;
	}

	Normal& Normal::operator-=(const Normal& _n)
	{
		x -= _n.x;
		y -= _n.y;
		z -= _n.z;
		return *this;
	}

	Normal& Normal::operator+=(const Normal& _n)
	{
		x += _n.x;
		y += _n.y;
		z += _n.z;
		return *this;
	}

	Normal& Normal::operator=(const Normal& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		return *this;
	}

	Normal operator+(const Normal& _n)
	{
		return _n;
	}

	Normal operator-(const Normal& _n)
	{
		Normal n;
		n.x = -_n.x;
		n.y = -_n.y;
		n.z = -_n.z;
		return n;
	}

	Normal operator+(const Normal& _n1, const Normal& _n2)
	{
		Normal n;
		n.x = _n1.x + _n2.x;
		n.y = _n1.y + _n2.y;
		n.z = _n1.z + _n2.z;
		return n;
	}


	Normal operator-(const Normal& _n1, const Normal& _n2)
	{
		Normal n;
		n.x = _n1.x - _n2.x;
		n.y = _n1.y - _n2.y;
		n.z = _n1.z - _n2.z;
		return n;
	}

	Normal operator*(const Normal& _n, float _f)
	{
		Normal n;
		n.x = _n.x * _f;
		n.y = _n.y * _f;
		n.z = _n.z * _f;
		return n;
	}

	Normal operator*(float _f, const Normal& _n)
	{
		Normal n;
		n.x = _f * _n.x;
		n.y = _f * _n.y;
		n.z = _f * _n.z;
		return n;
	}
}