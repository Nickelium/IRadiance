#pragma once

#include "Object.h"

namespace IRadiance
{
	class Sphere : public Object
	{
	public:
		Point c;
		float r;

		RGBSpectrum m_Color;

		Sphere(const Point& _c = {0, 0, 0}, float radius = 1.0f);
		virtual bool Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const override;
		virtual RGBSpectrum GetColor() const override;

		void SetCenter(const Point& _c);
		void SetRadius(float _r);
		void SetColor(const RGBSpectrum& _color);
	};
}
