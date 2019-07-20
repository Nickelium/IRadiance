#include "pch.h"
#include "Plane.h"

namespace IRadiance
{ 
	Plane::Plane(const Point& _p, const Normal& _n)
		: p(_p), n(_n)
	{
	}

	bool Plane::Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const
	{
		float t = Dot(p - _ray.o, n) / Dot(_ray.d, n);
		if (t > 1e-3f)
		{
			_tMin = t;
			_sr.hasHit = true;
			_sr.hitPoint = _ray.o + t * _ray.d;
			_sr.normal = n;
			_sr.t = t;

			return true;
		}
		else return false;
	}

}