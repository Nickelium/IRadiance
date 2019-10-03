#pragma once

#include "Object.h"

namespace IRadiance
{
	class Sphere : public Object
	{
	public:
		Point3 c;
		float r;

		Sphere(const Point3& _c = {0, 0, 0}, float radius = 1.0f);
		virtual bool Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const override;
		virtual bool ShadowHit(const Ray& _ray, float& _t) const override;


		void SetCenter(const Point3& _c);
		void SetRadius(float _r);

		static const float eps;
	};
}
