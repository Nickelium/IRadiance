#include "pch.h"
#include "Disk.h"

namespace IRadiance
{
	const float Disk::eps = 1e-3f;

	Disk::Disk(const Point3& _c, float _r, const Vector& _n)
		: c(_c), r(_r), n(Normalize(_n)), invArea( 1.0f / (Constants::PI * _r * _r) )
	{
	}

	bool Disk::Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const
	{
		float denom = Dot(n, _ray.d);
		if (abs(denom) < 1e-3f)
			return false;

		float t = (-Dot(n, _ray.o) + Dot(n, c)) / denom;

		if (t < eps)
			return false;

		Point3 p = _ray.o + t * _ray.d;

		bool inDisk = LengthSquared(c - p) <= r * r;
		if (inDisk)
		{
			_tMin = t;
			_sr.normal = n;
		}
		return false;
	}

	bool Disk::ShadowHit(const Ray& _ray, float& _t) const
	{
		if (!m_Shadow)
			return false;

		float denom = Dot(n, _ray.d);
		if (abs(denom) < 1e-3f)
			return false;

		float t = (-Dot(n, _ray.o) + Dot(n, c)) / denom;
		Point3 p = _ray.o + t * _ray.d;

		bool inDisk = LengthSquared(c - p) <= r * r;
		if (inDisk)
		{
			_t = t;
		}
		return false;

	}

	Point3 Disk::Sample() const
	{
		Point2 p = (*m_Sampler)->SamplesUnitDisk();
		Vector q {p.x * r, p.y * r, 0.0f};

		//TODO rotate q from {0,1,0} to n

		return q + c;
	}

	float Disk::pdf(const HitRecord&) const
	{
		return invArea;
	}

	Vector Disk::Normal(const Point3&) const
	{
		return n;
	}

}
