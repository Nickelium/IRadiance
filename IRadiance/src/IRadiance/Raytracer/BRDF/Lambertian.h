#pragma once

#include "BRDF.h"

namespace IRadiance
{
	class Lambertian : public BRDF
	{
	public:
		virtual RGBSpectrum f(const HitRecord& _hr, const Vector& wO, const Vector& wI) const override;
		virtual RGBSpectrum Sample_f(const HitRecord& _hr, const Vector& wO, Vector& wI, float& pdf) const override;
		virtual RGBSpectrum rho(const HitRecord& _hr, const Vector& wO) const override;

		void SetKa(float _ka);
		void SetKd(float _kd);
		void SetCd(const RGBSpectrum& _cd);
	private:
		// reflectance rho = kd * cd
		float kd;
		RGBSpectrum cd;
	};
}
