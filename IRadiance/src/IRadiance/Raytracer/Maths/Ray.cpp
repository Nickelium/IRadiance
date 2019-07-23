#include "pch.h"
#include "Ray.h"

namespace IRadiance 
{
	Ray::Ray()
	{
	}

	Ray::Ray(const Point3& _origin, const Vector& _direction)
		: o(_origin), d(_direction)
	{
	}

	Ray::Ray(const Ray& _other)
		: Ray(_other.o, _other.d)
	{
	}

	Ray& Ray::operator=(const Ray& _other)
	{
		o = _other.o;
		d = _other.d;
		return *this;
	}
}