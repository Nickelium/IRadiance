#pragma once

#include "Object.h"

namespace IRadiance
{
	class Triangle : public Object
	{
	public:
		Triangle(const Point3& _p0, const Point3& _p1, const Point3& _p2);
		Triangle(const Point3& _p0, const Point3& _p1, const Point3& _p2, const Vector& _n);
		virtual bool Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const override;
		virtual bool ShadowHit(const Ray& _ray, float& _t) const override;

		virtual Point3 Sample() const override;
		virtual float pdf(const HitRecord&) const override;
		virtual Vector Normal(const Point3&) const override;
	private:
		Point3 p0, p1, p2;
		Vector n;

		float invArea;

		static const float eps;
	};
}
