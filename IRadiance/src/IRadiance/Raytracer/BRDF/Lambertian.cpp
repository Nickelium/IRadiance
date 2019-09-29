#include "pch.h"
#include "Lambertian.h"

namespace IRadiance
{
	RGBSpectrum IRadiance::Lambertian::f(const HitRecord& _hr, const Vector& wO, const Vector& /*wI*/) const
	{
		//return rho / pi
		//return kd * cd * Constants::invPI;
		return rho(_hr, wO) * Constants::invPI;
	}

	RGBSpectrum IRadiance::Lambertian::Sample_f(const HitRecord& _hr, const Vector& wO, Vector& /*wI*/) const
	{
		//TODO pdf
		return rho(_hr, wO) * Constants::invPI;
	}

	RGBSpectrum IRadiance::Lambertian::rho(const HitRecord& /*_hr*/, const Vector& /*wO*/) const
	{
		//reflectance rho = kd * cd
		return kd * cd;
	}

	void Lambertian::SetKa(float _ka)
	{
		kd = _ka;
	}

	void Lambertian::SetKd(float _kd)
	{
		kd = _kd;
	}

	void Lambertian::SetCd(const RGBSpectrum& _cd)
	{
		cd = _cd;
	}

} 