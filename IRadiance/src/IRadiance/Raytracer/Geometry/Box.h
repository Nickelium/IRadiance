#pragma once

#include "Object.h"

namespace IRadiance
{
	class Box : public Object
	{
	public:
		Box(const Point3& _minPoint, const Point3& _maxPoint);
		virtual bool Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const override;
		virtual bool ShadowHit(const Ray&, float&) const override;

		Vector Normal(const int _faceHit) const;

	private:
		Point3 minPoint;
		Point3 maxPoint;

		static const float eps;
	};
}
