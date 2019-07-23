#include "pch.h"
#include "Vector.h"

#include "Point3.h"
#include "Normal.h"

namespace IRadiance
{
	Vector::Vector(float _value)
		: Vector(_value, _value, _value)
	{
	}

	Vector::Vector(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{
	}

	Vector::Vector(const Vector& _other)
		: Vector(_other.x, _other.y, _other.z)
	{
	}


	Vector::Vector(const Point3& _p)
		: Vector(_p.x, _p.y, _p.z)
	{
	}

	Vector::Vector(const Normal& _n)
		: Vector(_n.x, _n.y, _n.z)
	{

	}

	Vector& Vector::Normalize()
	{
		return *this /= Length(*this);
	}

	Vector& Vector::operator/=(float _f)
	{
		float invF = 1.0f / _f;
		x *= invF;
		y *= invF;
		z *= invF;
		return *this;
	}

	Vector& Vector::operator*=(float _f)
	{
		x *= _f;
		y *= _f;
		z *= _f;
		return *this;
	}

	Vector& Vector::operator-=(const Vector& _other)
	{
		return *this += (-_other);
	}

	Vector& Vector::operator+=(const Vector& _other)
	{
		x += _other.x;
		y += _other.y;
		z += _other.z;
		return *this;
	}

	Vector& Vector::operator=(const Vector& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		return *this;
	}

	Vector operator+(const Vector& _v)
	{
		return _v;
	}

	Vector operator-(const Vector& _v)
	{
		return Vector(-_v.x, -_v.y, -_v.z);
	}

	Vector operator+(const Vector& _v1, const Vector& _v2)
	{
		Vector v;
		v.x = _v1.x + _v2.x;
		v.y = _v1.y + _v2.y;
		v.z = _v1.z + _v2.z;
		return v;
	}

	Vector operator-(const Vector& _v1, const Vector& _v2)
	{
		Vector v;
		v.x = _v1.x - _v2.x;
		v.y = _v1.y - _v2.y;
		v.z = _v1.z - _v2.z;
		return v;
	}

	Vector operator*(const Vector& _v, float _f)
	{
		Vector v;
		v.x = _v.x * _f;
		v.y = _v.y * _f;
		v.z = _v.z * _f;
		return v;
	}

	Vector operator*(float _f, const Vector& _v)
	{
		return _v * _f;
	}

	Vector operator/(const Vector& _v, float _f)
	{
		return _v * (1.0f / _f);
	}

	float Length(const Vector& _v)
	{
		float len = _v.x * _v.x + _v.y * _v.y + _v.z * _v.z;
		return sqrt(len);
	}

	float LengthSquared(const Vector& _v)
	{
		return _v.x * _v.x + _v.y * _v.y + _v.z * _v.z;
	}


	Vector Normalize(const Vector& _v)
	{
		Vector v = _v;
		float len = Length(v);
		return v / len;
	}

	float Dot(const Vector& _v1, const Vector& _v2)
	{
		return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z;
	}

	Vector Cross(const Vector& _v1, const Vector& _v2)
	{
		Vector v;
		v.x = _v1.y * _v2.z - _v2.y * _v1.z;
		v.y = -_v1.x * _v2.z + _v2.x * _v1.z;
		v.z = _v1.x * _v2.y - _v2.x * _v1.y;
		return v;
	}
}