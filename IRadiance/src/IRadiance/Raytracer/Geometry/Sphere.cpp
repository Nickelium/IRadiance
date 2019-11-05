#include "pch.h"
#include "Sphere.h"

namespace IRadiance
{
	const float Sphere::eps = 1e-2f;

	Sphere::Sphere(const Point3& _c /*= {0, 0, 0}*/, float radius /*= 1.0f*/)
		: c(_c), r(radius)
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

			if (t > eps)
			{
				_tMin = t;
				_sr.localHitPoint = _ray.o + t * _ray.d;
				_sr.normal = Normal(_sr.localHitPoint);
				return true;	
			}

			t = (-B + sqrtD) / denom;

			if (t > eps)
			{
				_tMin = t;
				_sr.localHitPoint = _ray.o + t * _ray.d;
				_sr.normal = Normal(_sr.localHitPoint);
				return true;
			}
			return false;
		}
		else return false;
	}

	bool Sphere::ShadowHit(const Ray& _ray, float& _t) const
	{
		if (!m_Shadow)
			return false;
		float A = Dot(_ray.d, _ray.d);
		float B = 2 * Dot(_ray.o - this->c, _ray.d);
		float C = Dot(_ray.o - this->c, _ray.o - this->c) - r * r;
		float D = B * B - 4 * A * C;
		if (D >= 0)
		{
			float sqrtD = sqrt(D);
			float denom = 2 * A;
			float t = (-B - sqrtD) / denom;

			if (t > eps)
			{
				_t = t;
				return true;
			}

			t = (-B + sqrtD) / denom;

			if (t > eps)
			{
				_t = t;
				return true;
			}
			return false;
		}
		else return false;
	}

	void Sphere::SetCenter(const Point3& _c)
	{
		c = _c;
	}

	void Sphere::SetRadius(float _r)
	{
		r = _r;
	}

	Point3 Sphere::Sample() const
	{
		Point3 p = (*m_Sampler)->SampleHemisphere();
		return c + p * r;
	}

	float Sphere::pdf(const HitRecord&) const
	{
		return Constants::InvTwoPI;
	}

	Vector Sphere::Normal(const Point3& _p) const
	{
		return (_p - c) / r;
	}
}