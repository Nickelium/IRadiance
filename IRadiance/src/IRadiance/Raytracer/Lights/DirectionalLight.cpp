#include "pch.h"
#include "DirectionalLight.h"

namespace IRadiance
{

	DirectionalLight::DirectionalLight(float _ls /*= 1.0f*/, const RGBSpectrum& _c /*= WHITE*/, const Vector& _direction /*= {0.0f, 1.0f, 0.0f}*/)
		: ls(_ls), c(_c), direction(_direction)
	{
	}

	Vector DirectionalLight::GetDirection(HitRecord& /*_hr*/) const
	{
		return direction;
	}

	RGBSpectrum DirectionalLight::L(HitRecord& /*_hr*/) const
	{
		return ls * c;
	}

	void DirectionalLight::SetLs(float _ls)
	{
		ls = _ls;
	}

	void DirectionalLight::SetC(const RGBSpectrum& _c)
	{
		c = _c;
	}

	void DirectionalLight::SetDirection(const Vector& _direction)
	{
		direction = Normalize(_direction);
	}

}