#include "pch.h"
#include "PerfectTransmitter.h"

namespace IRadiance
{
	PerfectTransmitter::PerfectTransmitter(const RGBSpectrum& _kt /*= WHITE*/, float _ior /*= 1.0f*/)
		: ct(_kt), ior(_ior)
	{
	}

	//Not used because this is delta function
	RGBSpectrum PerfectTransmitter::f(const HitRecord& /*_hr*/, const Vector& /*wO*/, const Vector& /*wI*/) const
	{
		return BLACK;
	}

	RGBSpectrum PerfectTransmitter::Sample_f(const HitRecord& _hr, const Vector& wO, Vector& wT, float& /*pdf*/) const
	{
		Vector n = _hr.normal;
		float cosThetaI = Dot(wO, n);
		float eta = ior;

		if (cosThetaI < 0.0f)
		{
			eta = 1.0f / eta;
			n = -n;
			cosThetaI = -cosThetaI;
		}

		float costThetaT = sqrt(1.0f - (1.0f - cosThetaI * cosThetaI) / (eta * eta));
		wT = -wO / eta - (costThetaT - cosThetaI / eta) * n;


		return (ct * eta * eta) / abs(Dot(wT, _hr.normal)); //BTDF
	}

	RGBSpectrum PerfectTransmitter::rho(const HitRecord& /*_hr*/, const Vector& /*wO*/) const
	{
		return BLACK;
	}

	bool PerfectTransmitter::Tir(const HitRecord& _hr) const
	{
		Vector wO = -_hr.ray.d;
		float cosThetaI = Dot(wO, _hr.normal);
		float eta = ior;
		if (cosThetaI < 0.0f)
			return eta = 1.0f / eta; // invert ior when inside other medium
		bool tir = 1.0f - (1.0f - cosThetaI * cosThetaI) / (eta * eta) < 0.0f;
		return tir;
		//return 1.0f - (1.0f / (eta * eta)) * (1.0f - cosThetaI * cosThetaI) <= 0.0f;
	}

	void PerfectTransmitter::SetCt(const RGBSpectrum& _ct)
	{
		ct = _ct;
	}

	void PerfectTransmitter::SetIOR(float _ior)
	{
		ior = _ior;
	}

}