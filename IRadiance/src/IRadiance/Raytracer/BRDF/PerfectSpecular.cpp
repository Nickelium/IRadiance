#include "pch.h"
#include "PerfectSpecular.h"

namespace IRadiance
{
	//This is a diract delta BRDF therefore, f & rho doesn't apply
	RGBSpectrum PerfectSpecular::f(const HitRecord& /*_hr*/, const Vector& /*wO*/, const Vector& /*wI*/) const
	{
		return BLACK;
	}

	RGBSpectrum PerfectSpecular::Sample_f(const HitRecord& _hr, const Vector& wO, Vector& wI, float& pdf) const
	{
		wI = -wO + 2.0f * Dot(wO, _hr.normal) * _hr.normal;
		pdf = Dot(wI, _hr.normal);

		return (kr * cr) / Dot(_hr.normal, wI);
	}

	RGBSpectrum PerfectSpecular::rho(const HitRecord& /*_hr*/, const Vector& /*wO*/) const
	{
		return BLACK;
	}

	void PerfectSpecular::SetKr(float _kr)
	{
		kr = _kr;
	}

	void PerfectSpecular::SetCr(const RGBSpectrum& _cr)
	{
		cr = _cr;
	}

}