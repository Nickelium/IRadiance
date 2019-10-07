#pragma once

#include "Object.h"

#include "IRadiance/Raytracer/Maths/Point3.h"

namespace IRadiance
{
	class Plane : public Object
	{
	public:
		Point3 p;
		Vector n;

		Plane(const Point3& _p = { 0, 0, 0 }, const Vector& _n = {0, 1, 0});
		virtual bool Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const override;
		virtual bool ShadowHit(const Ray& _ray, float& _t) const override;

		void SetPoint(const Point3& _p);
		void SetNormal(const Vector& _n);

		static const float eps;
	};
}
