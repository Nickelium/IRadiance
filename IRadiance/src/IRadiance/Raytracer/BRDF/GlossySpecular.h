#pragma once

#include "IRadiance/Raytracer/BRDF/BRDF.h"

namespace IRadiance
{
	class GlossySpecular : public BRDF
	{
	public:
		GlossySpecular(const RGBSpectrum& _ks = WHITE, float _exp = 1.0f, const RGBSpectrum& _cs  = WHITE);
		virtual RGBSpectrum f(const HitRecord& _hr, const Vector& wO, const Vector& wI) const override;
		virtual RGBSpectrum Sample_f(const HitRecord& _hr, const Vector& wO, Vector& wI, float& pdf) const override;
		virtual RGBSpectrum rho(const HitRecord& _hr, const Vector& wO) const override;

		void SetKs(const RGBSpectrum& _ks);
		void SetExp(float _exp);
		void SetCs(const RGBSpectrum& _cs);
	private:
		RGBSpectrum ks;
		float exp;

		// Extra to manipulate highlight color (some form of hack)
		RGBSpectrum cs;
	};
}
