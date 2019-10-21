#pragma once

#include "Object.h"

namespace IRadiance
{
	class Disk : public Object
	{
	public:
		Disk(const Point3& _c, float _r, const Vector& _n);
		virtual bool Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const override;
		virtual bool ShadowHit(const Ray& _ray, float& _t) const override;

		virtual Point3 Sample() const override;
		virtual float pdf(const HitRecord&) const override;
		virtual Vector Normal(const Point3&) const override;

	private:
		Point3 c;
		float r;

		Vector n;

		float invArea;

		static const float eps;
	};
}
