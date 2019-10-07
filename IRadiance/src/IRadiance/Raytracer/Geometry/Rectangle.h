#pragma once

#include "Object.h"

namespace IRadiance
{
	class Rectangle : public Object
	{
	public:
		Rectangle(const Point3& _p0, const Vector& _a = { 1.0f, 0.0f, 0.0f }, const Vector& _b = { 0.0f, 1.0f, 0.0f });
		virtual bool Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const override;
		virtual bool ShadowHit(const Ray&, float&) const override;

		virtual Point3 Sample() const override;
		virtual float pdf(const HitRecord& _hr) const override;
		virtual Vector Normal(const Point3& _p) const override;

	private:
		Point3 p0;
		Vector i; // unit vector
		Vector j; // unit vector
		float sizeI, sizeJ;
		Vector n;

		static const float eps;

		float area;
		float invArea;
	};
}
