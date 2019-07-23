#pragma once

namespace IRadiance
{
	class Point;
	class Normal;
	/**
		* Vector with 3 Components
		*/
	class Vector
	{
	public:
		float x, y, z;

		Vector(float _value = 0.0f);
		Vector(float _x, float _y, float _z);
		Vector(const Vector& _other);
		Vector(const Point& _p);
		Vector(const Normal& _n);

		Vector& operator=(const Vector& _other);

		Vector& operator+=(const Vector& _other);
		Vector& operator-=(const Vector& _other);
		Vector& operator*=(float _f);
		Vector& operator/=(float _f);

		Vector& Normalize();
	};

	Vector operator+(const Vector& _v);
	Vector operator-(const Vector& _v);

	Vector operator+(const Vector& _v1, const Vector& _v2);
	Vector operator-(const Vector& _v1, const Vector& _v2);
	Vector operator*(const Vector& _v, float _f);
	Vector operator*(float _f, const Vector& _v);
	Vector operator/(const Vector& _v, float _f);

	float Length(const Vector& _v);
	float LengthSquared(const Vector& _v);

	Vector Normalize(const Vector& _v);

	float Dot(const Vector& _v1, const Vector& _v2);
	Vector Cross(const Vector& _v1, const Vector& _v2);
}
