#include "pch.h"
#include "AmbientLight.h"

namespace IRadiance
{
	AmbientLight::AmbientLight(float _ls /*= 1.0f*/, const RGBSpectrum& _c /*= WHITE*/)
		: Light(), ls(_ls), c(_c)
	{
	}

	Vector AmbientLight::GetDirection(HitRecord& _hr)
	{
		//Ambient Light doesn't have position nor direction
		return Vector(0.0f, 0.0f, 0.0f);
	}

	RGBSpectrum AmbientLight::L(HitRecord& _hr)
	{
		return ls * c;
	}
}