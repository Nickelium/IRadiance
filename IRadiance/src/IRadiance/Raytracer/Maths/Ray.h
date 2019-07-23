#pragma once

#include "Point3.h"
#include "Vector.h"

namespace IRadiance
{
	class Ray
	{
	public:
		Point3 o;
		Vector d;

		Ray();
		Ray(const Point3& _origin, const Vector& _direction);
		Ray(const Ray& _other);

		Ray& operator=(const Ray& _other);
	};
}
