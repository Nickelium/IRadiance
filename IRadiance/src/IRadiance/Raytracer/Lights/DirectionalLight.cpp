#include "pch.h"
#include "DirectionalLight.h"

namespace IRadiance
{
	Vector DirectionalLight::GetDirection(HitRecord& _hr)
	{
		return direction;
	}

	RGBSpectrum DirectionalLight::L(HitRecord& _hr)
	{
		return ls * c;
	}
}