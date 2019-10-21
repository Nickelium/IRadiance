#include "pch.h"
#include "OpenCylinder.h"

namespace IRadiance
{
	const float OpenCylinder::eps = 1e-3f;

	OpenCylinder::OpenCylinder(float _r /*= 1.0f*/, float _y0 /*= -1.0f*/, float _y1 /*= 1.0f*/)
		: r(_r), y0(_y0), y1(_y1)
	{
	}

	bool OpenCylinder::Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const
	{
		float a = _ray.d.x * _ray.d.x + _ray.d.z * _ray.d.z;
		float b = 2.0f * (_ray.o.x * _ray.d.x + _ray.o.z * _ray.d.z);
		float c = _ray.o.x * _ray.o.x + _ray.o.z * _ray.o.z - r * r;

		float sqrtD = b * b - 4 * a * c;
		if (sqrtD < 0.0f)
			return false;
		float D = sqrt(sqrtD);
		float denom = 2 * a;
		float t = (-b - D) / denom;

		Point3 p = _ray.o + t * _ray.d;
		if (t > eps && 
			y0 <= p.y && p.y <= y1)
		{
			_tMin = t;
			_sr.normal = Vector{ p.x, 0.0f, p.z } / r;
			return true;
		}

		t = (-b + D) / denom;
		p = _ray.o + t * _ray.d;
		if (t > eps &&
			y0 <= p.y && p.y <= y1)
		{
			_tMin = t;
			_sr.normal = Vector{ p.x, 0.0f, p.z } / r;
			return true;
		}
		return false;
	}

	bool OpenCylinder::ShadowHit(const Ray& _ray, float& _t) const
	{
		if (!m_Shadow)
			return false;
		
		float a = _ray.d.x * _ray.d.x + _ray.d.z * _ray.d.z;
		float b = 2.0f * (_ray.o.x * _ray.d.x + _ray.o.z * _ray.d.z);
		float c = _ray.o.x * _ray.o.x + _ray.o.z * _ray.o.z - r * r;

		float sqrtD = b * b - 4 * a * c;
		if (sqrtD < 0.0f)
			return false;
		float D = sqrt(sqrtD);
		float denom = 2 * a;
		float t = (-b - D) / denom;

		Point3 p = _ray.o + t * _ray.d;
		if (t > eps &&
			y0 <= p.y && p.y <= y1)
		{
			_t = t;
			return true;
		}

		t = (-b + D) / denom;
		p = _ray.o + t * _ray.d;
		if (t > eps &&
			y0 <= p.y && p.y <= y1)
		{
			_t = t;
			return true;
		}
		return false;
	}

	Point3 OpenCylinder::Sample() const
	{
		//TODO
		return {};
	}

	float OpenCylinder::pdf(const HitRecord&) const
	{
		//TODO
		return 0.0f;
	}

	Vector OpenCylinder::Normal(const Point3& _p) const
	{
		return Vector{ _p.x, 0.0f, _p.z } / r;
	}

}