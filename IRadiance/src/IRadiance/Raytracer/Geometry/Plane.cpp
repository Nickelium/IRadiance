#include "pch.h"
#include "Plane.h"

namespace IRadiance
{ 
	Plane::Plane(const Point3& _p, const Normal& _n)
		: p(_p), n(_n), m_Color(BLACK)
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

	RGBSpectrum Plane::GetColor() const
	{
		return m_Color;
	}

	void Plane::SetPoint(const Point3& _p)
	{
		p = _p;
	}

	void Plane::SetNormal(const Normal& _n)
	{
		n = _n;
	}

	void Plane::SetColor(const RGBSpectrum& _color)
	{
		m_Color = _color;
	}

}