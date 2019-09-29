#include "pch.h"
#include "AmbientLight.h"

namespace IRadiance
{
	AmbientLight::AmbientLight(float _ls /*= 1.0f*/, const RGBSpectrum& _c /*= WHITE*/)
		: Light(), ls(_ls), c(_c)
	{
	}

	Vector AmbientLight::GetDirection(HitRecord& /*_hr*/) const
	{
		//Ambient Light doesn't have position nor direction
		return Vector(0.0f, 0.0f, 0.0f);
	}

	RGBSpectrum AmbientLight::L(HitRecord& /*_hr*/) const
	{
		return ls * c;
	}

	void AmbientLight::SetLs(float _ls)
	{
		ls = _ls;
	}

	void AmbientLight::SetC(const RGBSpectrum& _c)
	{
		c = _c;
	}

}