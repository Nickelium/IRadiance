#pragma once

#include "Object.h"

namespace IRadiance
{
	class OpenCylinder : public Object
	{
	public:
		OpenCylinder(float _r = 1.0f, float _y0 = -1.0f, float _y1 = 1.0f);
		virtual bool Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const override;
		virtual bool ShadowHit(const Ray& _ray, float& _t) const override;
	
		virtual Point3 Sample() const override;
		virtual float pdf(const HitRecord&) const override;
		virtual Vector Normal(const Point3& _p) const override;
	private:
		float r;
		float y0;
		float y1;

		static const float eps;
	};
}
