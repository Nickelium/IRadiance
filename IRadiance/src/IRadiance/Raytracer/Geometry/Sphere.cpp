#include "pch.h"
#include "Sphere.h"

namespace IRadiance
{
	Sphere::Sphere(const Point3& _c /*= {0, 0, 0}*/, float radius /*= 1.0f*/)
		: c(_c), r(radius), m_Color(RED)
	{
	}

	bool Sphere::Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const
	{
		float A = Dot(_ray.d, _ray.d);
		float B = 2 * Dot(_ray.o - this->c, _ray.d);
		float C = Dot(_ray.o - this->c, _ray.o - this->c) - r * r;
		float D = B * B - 4 * A * C;
		if (D >= 0)
		{
			float sqrtD = sqrt(D);
			float denom = 2 * A;
			float t = (-B - sqrtD) / denom;

			if (t > 1e-3f)
			{
				_tMin = t;
				_sr.hasHit = true;
				_sr.hitPoint = _ray.o + t * _ray.d;
				_sr.t = t;
				_sr.normal = (_sr.hitPoint - c) / r;
				return true;	
			}

			t = (-B + sqrtD) / denom;

			if (t > 1e-3f)
			{
				_tMin = t;
				_sr.hasHit = true;
				_sr.hitPoint = _ray.o + t * _ray.d;
				_sr.t = t;
				_sr.normal = (_sr.hitPoint - _ray.o) / r;
				return true;
			}
			return false;
		}
		else return false;
	}

	RGBSpectrum Sphere::GetColor() const
	{
		return m_Color;
	}

	void Sphere::SetCenter(const Point3& _c)
	{
		c = _c;
	}

	void Sphere::SetRadius(float _r)
	{
		r = _r;
	}

	void Sphere::SetColor(const RGBSpectrum& _color)
	{
		m_Color = _color;
	}

}