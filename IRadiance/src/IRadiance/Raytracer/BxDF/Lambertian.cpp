#include "pch.h"
#include "Lambertian.h"

namespace IRadiance
{
	RGBSpectrum Lambertian::f(const HitRecord& _hr, const Vector& wO, const Vector& /*wI*/) const
	{
		//return rho / pi
		//return kd * cd * Constants::invPI;
		return rho(_hr, wO) * Constants::InvPI;
	}

	RGBSpectrum Lambertian::Sample_f(const HitRecord& _hr, const Vector& wO, Vector& wI, float& pdf) const
	{
		Vector w = _hr.normal;
		Vector u = Normalize(Cross({0.0034f, 1.0f, 0.0071f}, w));
		Vector v = Cross(u, w);

		IRAD_CORE_ASSERT(m_Sampler, "Pointer Sampler is nullptr");
		IRAD_CORE_ASSERT(*m_Sampler, "Sampler is nullptr");
		Point3 p = (*m_Sampler)->SampleHemisphere();

		wI = Normalize(p.x * u + p.y * v + p.z * w);
		pdf = Dot(wI, _hr.normal) * Constants::InvPI;
		//pdf = 1.0f / Constants::TwoPi;
		return rho(_hr, wO) * Constants::InvPI;
	}

	RGBSpectrum Lambertian::rho(const HitRecord& /*_hr*/, const Vector& /*wO*/) const
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