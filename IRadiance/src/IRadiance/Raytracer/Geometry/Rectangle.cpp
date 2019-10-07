#include "pch.h"
#include "Rectangle.h"
#include "IRadiance/Raytracer/Samplers/Sampler.h"

namespace IRadiance
{
	const float Rectangle::eps = 1e-3f;

	Rectangle::Rectangle(const Point3& _p0, const Vector& _a, const Vector& _b)
		: p0(_p0), i(Normalize(_a)), j(Normalize(_b)), sizeI(Length(_a)), sizeJ(Length(_b)), 
		n(Normalize(Cross(i, j))), area(sizeI * sizeJ), invArea(1.0f / area)
	{
	}

	bool Rectangle::Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const
	{
		float t = Dot(p0 - _ray.o, n) / Dot(_ray.d, n);
		if (t <= eps)
			return false;
		Point3 p = _ray.o + t * _ray.d;
		Vector d = p - p0;
		//Compare d with the rectangle
		float dProji = Dot(d, i * sizeI);
		if (dProji < 0.0f || dProji > sizeI * sizeI)
			return false;

		float dProjJ = Dot(d, j * sizeJ);
		if (dProjJ < 0.0f || dProjJ > sizeJ * sizeJ)
			return false;

		_tMin = t;
		_sr.localHitPoint = p;
		_sr.normal = n;

		return true;
	}

	bool Rectangle::ShadowHit(const Ray& _ray, float& _t) const
	{
		float t = Dot(p0 - _ray.o, n) / Dot(_ray.d, n);
		if (t <= eps)
			return false;
		Point3 p = _ray.o + t * _ray.d;
		Vector d = p - p0;
		//Compare d with the rectangle
		float dProji = Dot(d, i * sizeI);
		if (dProji < 0.0f || dProji > sizeI * sizeI)
			return false;

		float dProjJ = Dot(d, j * sizeJ);
		if (dProjJ < 0.0f || dProjJ > sizeJ * sizeJ)
			return false;

		_t = t;

		return true;
	}

	Point3 Rectangle::Sample() const
	{
		Point2 p = m_Sampler->SampleUnitSquare();
		return p0 + p.x * i * sizeI + p.y * j * sizeJ;
	}

	float Rectangle::pdf(const HitRecord& /*_hr*/) const
	{
		return invArea;
	}

	Vector Rectangle::Normal(const Point3& /*_p*/) const
	{
		return n;
	}

}