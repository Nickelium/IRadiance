#pragma once

#include "Light.h"

namespace IRadiance
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(float _ls = 1.0f, const RGBSpectrum & _c = WHITE, 
			const Vector & _direction = {0.0f, 1.0f, 0.0f});
		virtual Vector GetDirection(HitRecord& _hr) const override;
		virtual RGBSpectrum L(HitRecord& _hr) const override;

		void SetLs(float _ls);
		void SetC(const RGBSpectrum& _c);
		void SetDirection(const Vector& _direction);
	private:
		float ls;
		RGBSpectrum c;

		Vector direction;
	};
}
