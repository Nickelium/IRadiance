#include "pch.h"
#include "MultiObject.h"

#include "IRadiance/Raytracer/Maths/Utilities.h"

namespace IRadiance
{

	MultiObject::MultiObject(Renderer* _renderer)
		: m_Renderer(_renderer)
	{
	}

	RGBSpectrum MultiObject::RayTrace(const Ray& _ray)
	{
		float t;
		float tMin = std::numeric_limits<float>::max();
		HitRecord hr;
		const std::vector<Object*>& objects = m_Renderer->GetObjects();
		Normal normal;
		for (Object* object : objects)
		{
			if (object->Hit(_ray, t, hr) && t < tMin)
			{
				hr.color = object->GetColor();
				normal = hr.normal;
				tMin = t;
			}
		}

		if (hr.hasHit)
		{
			//IRAD_CORE_TRACE("{0}, {1}, {2} : normal", normal.x, normal.y, normal.z);
			//return 0.5f * (RGBSpectrum(normal.x, normal.y, normal.z) + RGBSpectrum{1, 1, 1});
			return Clamp(Dot(normal, -_ray.d), 0.0f, 1.0f) * hr.color;
		}
		else
			return m_Renderer->GetBackColor();
	}

}