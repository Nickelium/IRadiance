#pragma once

#include "Light.h"

namespace IRadiance
{
	class PointLight : public Light
	{
	public:
		PointLight(float _ls = 1.0f, const RGBSpectrum & _c = WHITE,
			const Point3 & _p = { 0.0f, 0.0f, 0.0f }, bool _hasQuadraticFallOff = false);
		virtual Vector GetDirection(HitRecord& _hr) const override;
		virtual RGBSpectrum L(HitRecord& _hr) const override;

		void SetLs(float _ls);
		void SetC(const RGBSpectrum& _c);
		void SetPosition(const Point3& _position);

		void SetQuadraticFallOff(bool _hasQuadraticFallOff);
	private:
		float ls;
		RGBSpectrum c;

		Point3 position;

		bool m_HasQuadraticFallOff;
	};
}
