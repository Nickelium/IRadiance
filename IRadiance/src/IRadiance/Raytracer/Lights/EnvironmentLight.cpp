#include "pch.h"
#include "EnvironmentLight.h"

#include "IRadiance/Raytracer/Materials/Material.h"
#include "IRadiance/Raytracer/Renderer.h"

namespace IRadiance
{
	Vector EnvironmentLight::GetDirection(HitRecord& _hr) const
	{
		w = _hr.normal;
		v = Normalize(Cross(w, {0.0034f, 1.0f, 0.0071f})); // is basically the up vector with noise to avoid cross(y,y) == 0
		u = Normalize(Cross(v, w));
		Point3 p = (*m_Sampler)->SampleHemisphere();
		wI = p.x * u + p.y * v + p.z * w;
		return wI;
	}

	RGBSpectrum EnvironmentLight::L(HitRecord& /*_hr*/) const
	{
		return m_Material->Le();
	}

	bool EnvironmentLight::InShadow(const Ray& _ray, const HitRecord& _hr) const
	{
		float t;
		const auto& objects = _hr.renderer->GetScene()->GetObjects();
		for (auto object : objects)
		{
			if(!object->CastShadow())
				continue;
			if (object->ShadowHit(_ray, t))
				return true;
		}
		return false;
	}

	float EnvironmentLight::pdf(const HitRecord& _hr) const
	{
		return Dot(_hr.normal, wI) * Constants::InvPI;
	}

	void EnvironmentLight::SetSampler(Sampler** _sampler)
	{
		m_Sampler = _sampler;
	}

	void EnvironmentLight::SetMaterial(Material* _material)
	{
		m_Material = _material;
	}

}