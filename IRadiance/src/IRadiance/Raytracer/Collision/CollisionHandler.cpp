#include "pch.h"
#include "CollisionHandler.h"

#include "IRadiance/Raytracer/Geometry/Object.h"
#include "IRadiance/Raytracer/Renderer.h"

namespace IRadiance
{
	CollisionHandler::CollisionHandler(Renderer* _renderer)
		: m_Renderer(_renderer)
	{
	}

	HitRecord CollisionHandler::HitObjects(const Ray& _ray)
	{
		float t;
		float tMin = Constants::MaxValue;
		Normal normal;
		HitRecord hr(m_Renderer);
		const auto& objects = m_Renderer->GetScene()->GetObjects();
		for (auto object : objects)
		{
			if (object->Hit(_ray, t, hr) && t < tMin)
			{
				hr.hasHit = true;
				hr.hitPoint = _ray.o + t * _ray.d;
				hr.material = object->GetMaterial();
				normal = hr.normal;
				tMin = t;
			}
		}

		if (hr.hasHit)
		{
			hr.t = tMin;
			hr.normal = normal;
		}

		return hr;

	}
}