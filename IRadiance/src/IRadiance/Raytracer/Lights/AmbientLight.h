#pragma once

#include "Light.h"

namespace IRadiance
{
	class AmbientLight : public Light
	{
	public:
		AmbientLight(float _ls = 1.0f, const RGBSpectrum& _c = WHITE);
		virtual Vector GetDirection(HitRecord& _hr) override;
		virtual RGBSpectrum L(HitRecord& _hr) override;
	private:
		float ls; //Radiance Scaling 
		RGBSpectrum c; //Radiance
	};
}
