#pragma once

#include "BRDF.h"

namespace IRadiance
{
	class PerfectSpecular : public BRDF
	{
	public:
		PerfectSpecular();
		virtual RGBSpectrum f(const HitRecord& _hr, const Vector& wO, const Vector& wI) const override;
		virtual RGBSpectrum Sample_f(const HitRecord& _hr, const Vector& wO, Vector& wI, float& pdf) const override;
		virtual RGBSpectrum rho(const HitRecord& _hr, const Vector& wO) const override;

		void SetKr(float _kr);
		void SetCr(const RGBSpectrum& _cr);
	private:
		float kr;
		RGBSpectrum cr;
	};
}
