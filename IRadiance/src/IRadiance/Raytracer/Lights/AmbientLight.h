#pragma once

#include "Light.h"

namespace IRadiance
{
	class AmbientLight : public Light
	{
	public:
		AmbientLight(float _ls = 1.0f, const RGBSpectrum& _c = WHITE);
		virtual Vector GetDirection(HitRecord& _hr) const override;
		virtual RGBSpectrum L(HitRecord& _hr) const override;
		virtual bool InShadow(const Ray&, const HitRecord&) const override { return false; }

		void SetLs(float _ls);
		void SetC(const RGBSpectrum& _c);
	private:
		float ls; //Radiance Scaling 
		RGBSpectrum c; //Radiance
	};
}
