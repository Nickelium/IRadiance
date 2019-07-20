#pragma once

#include "IRadiance/Raytracer/Maths/Ray.h"
#include "HitRecord.h"

namespace IRadiance
{
	class Object
	{
	public:
		virtual bool Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const = 0;
	};
	
}
