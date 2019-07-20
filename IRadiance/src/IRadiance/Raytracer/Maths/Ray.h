#pragma once

#include "Point.h"
#include "Vector.h"

namespace IRadiance
{
	class Ray
	{
	public:
		Point o;
		Vector d;

		Ray();
		Ray(const Point& _origin, const Vector& _direction);
		Ray(const Ray& _other);

		Ray& operator=(const Ray& _other);
	};
}
