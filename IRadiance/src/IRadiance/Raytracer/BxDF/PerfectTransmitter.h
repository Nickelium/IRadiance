#pragma once

#include "BTDF.h"

namespace IRadiance
{
	class PerfectTransmitter : public BTDF
	{
	public:
		PerfectTransmitter(const RGBSpectrum& _kt = WHITE, float _ior = 1.0f);
		virtual RGBSpectrum f(const HitRecord& _hr, const Vector& wO, const Vector& wI) const override;
		virtual RGBSpectrum Sample_f(const HitRecord& _hr, const Vector& wO, Vector& wT, float& pdf) const override;
		virtual RGBSpectrum rho(const HitRecord& _hr, const Vector& wO) const override;
		virtual bool Tir(const HitRecord& _hr) const override;

		void SetCt(const RGBSpectrum& _ct);
		void SetIOR(float _ior);
	private:
		RGBSpectrum ct;
		float ior; //n = no/ni
	};
}
