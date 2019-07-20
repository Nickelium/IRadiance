#include "pch.h"
#include "SingleObject.h"

namespace IRadiance
{
	SingleObject::SingleObject(Renderer* _renderer)
		: m_Renderer(_renderer)
	{
	}

	RGBSpectrum SingleObject::RayTrace(const Ray& _ray)
	{
		float t;
		float tMin = std::numeric_limits<float>::max();
		tMin;
		HitRecord hr;
		bool hit = false;
		const std::vector<Object*>& objects = m_Renderer->GetObjects();
		objects;

		/*for (Object* object : objects)
		{
			if (object->Hit(_ray, t, hr) && t < tMin)
			{
				hit = true;
				hr.hasHit = true;
				hr.t = t;
				tMin = t;
			}
		}*/

		hit = m_Renderer->m_Sphere.Hit(_ray, t, hr);

		if (hit)
		{
			return RED;
		}
		else
			return WHITE;

	}

}