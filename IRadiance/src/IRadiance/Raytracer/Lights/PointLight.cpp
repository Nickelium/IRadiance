#include "pch.h"
#include "PointLight.h"

namespace IRadiance
{
	Vector PointLight::GetDirection(HitRecord& _hr)
	{
		return (position - _hr.hitPoint).Normalize();
	}

	RGBSpectrum PointLight::L(HitRecord& _hr)
	{
		return ls * c;
	}
}