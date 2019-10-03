#include "pch.h"
#include "DirectionalLight.h"

#include "IRadiance/Raytracer/Renderer.h"

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

	bool DirectionalLight::InShadow(const Ray& _r, const HitRecord& _hr) const
	{
		if (!m_Shadows)
			return false;
		float t;
		const auto& objects = _hr.renderer->GetScene()->GetObjects();
		for (auto object : objects)
		{
			if(object->ShadowHit(_r, t))
				return true;
		}
		return false;
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