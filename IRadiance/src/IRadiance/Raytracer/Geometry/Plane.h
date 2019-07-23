#pragma once

#include "Object.h"

#include "IRadiance/Raytracer/Maths/Point3.h"
#include "IRadiance/Raytracer/Maths/Normal.h"

namespace IRadiance
{
	class Plane : public Object
	{
	public:
		Point3 p;
		Normal n;

		RGBSpectrum m_Color;

		Plane(const Point3& _p = { 0, 0, 0 }, const Normal& _n = {0, 1, 0});
		virtual bool Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const override;
		virtual RGBSpectrum GetColor() const override;

		void SetPoint(const Point3& _p);
		void SetNormal(const Normal& _n);
		void SetColor(const RGBSpectrum& _color);
	};
}
