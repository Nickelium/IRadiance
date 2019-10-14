#include "pch.h"
#include "Emissive.h"

namespace IRadiance
{
	RGBSpectrum Emissive::Shading(HitRecord& _hr)
	{
		if(Dot(_hr.normal, -_hr.ray.d) > 0.0f)
			return Le();
		return BLACK;
	}

	RGBSpectrum Emissive::AreaLightShading(HitRecord& _hr)
	{
		if (Dot(_hr.normal, -_hr.ray.d) > 0.0f)
			return Le();
		return BLACK;
	}

	RGBSpectrum Emissive::PathShading(HitRecord& _hr)
	{
		if (Dot(_hr.normal, -_hr.ray.d) > 0.0f)
			return Le();
		return BLACK;
	}

	RGBSpectrum Emissive::HybridPathShading(HitRecord& _hr)
	{
		if (Dot(_hr.normal, -_hr.ray.d) > 0.0f)
			return Le();
		return BLACK;
	}

	void Emissive::SetLs(float _ls)
	{
		ls = _ls;
	}

	void Emissive::SetCe(const RGBSpectrum& _ce)
	{
		ce = _ce;
	}

	RGBSpectrum Emissive::Le() const
	{
		return ls * ce;
	}

}