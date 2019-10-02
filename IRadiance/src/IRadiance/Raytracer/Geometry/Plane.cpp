#include "pch.h"
#include "Plane.h"

namespace IRadiance
{ 
	Plane::Plane(const Point3& _p, const Vector& _n)
		: p(_p), n(_n)
	{
	}

	bool Plane::Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const
	{
		float t = Dot(p - _ray.o, n) / Dot(_ray.d, n);
		if (t > 1e-3f)
		{
			_tMin = t;
			_sr.localHitPoint= _ray.o + t * _ray.d;
			_sr.normal = n;

			return true;
		}
		else return false;
	}

	void Plane::SetPoint(const Point3& _p)
	{
		p = _p;
	}

	void Plane::SetNormal(const Vector& _n)
	{
		n = _n;
	}

}