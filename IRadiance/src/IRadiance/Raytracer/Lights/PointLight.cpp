#include "pch.h"
#include "PointLight.h"

namespace IRadiance
{

	PointLight::PointLight(float _ls /*= 1.0f*/, const RGBSpectrum& _c /*= WHITE*/, const Point3& _p /*= { 0.0f, 0.0f, 0.0f }*/)
		: ls(_ls), c(_c), position(_p)
	{
	}

	Vector PointLight::GetDirection(HitRecord& _hr) const
	{
		return (position - _hr.hitPoint).Normalize();
	}

	RGBSpectrum PointLight::L(HitRecord& /*_hr*/) const
	{
		return ls * c;
	}

	void PointLight::SetLs(float _ls)
	{
		ls = _ls;
	}

	void PointLight::SetC(const RGBSpectrum& _c)
	{
		c = _c;
	}

	void PointLight::SetPosition(const Point3& _position)
	{
		position = _position;
	}

}