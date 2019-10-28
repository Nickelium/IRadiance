#include "pch.h"
#include "AreaLight.h"

#include "IRadiance/Raytracer/Geometry/Object.h"
#include "IRadiance/Raytracer/Renderer.h"
#include "IRadiance/Raytracer/Materials/Material.h"

namespace IRadiance
{
	Vector AreaLight::GetDirection(HitRecord& _hr) const
	{
		samplePoint = m_Object->Sample();
		normal = m_Object->Normal(samplePoint);
		return wI = Normalize(samplePoint - _hr.hitPoint);
	}

	RGBSpectrum AreaLight::L(HitRecord& /*_hr*/) const
	{
		float nCosWi = Dot(normal, -wI);
		if(nCosWi > 0.0f)
			return m_Object->GetMaterial()->Le();
		return BLACK;
	}

	bool AreaLight::InShadow(const Ray& _ray, const HitRecord& _hr) const
	{
		float t;
		float d = Dot(samplePoint - _ray.o, _ray.d);
		const auto& objects = _hr.renderer->GetScene()->GetObjects();
		for (auto object : objects)
		{
			if (!object->CastShadow())
				continue;
			if(object == m_Object)
				continue;
			if (object->ShadowHit(_ray, t) && t < d)
				return true;
		}

		return false;
	}

	float AreaLight::G(const HitRecord& _hr) const
	{
		float nCosWi = Dot(normal, -wI);
		float dd = LengthSquared(_hr.hitPoint - samplePoint);
		return nCosWi / dd;
	}

	float AreaLight::pdf(const HitRecord& _hr) const
	{
		return m_Object->pdf(_hr);
	}

	void AreaLight::SetObject(Object* _object)
	{
		m_Object = _object;
	}

}