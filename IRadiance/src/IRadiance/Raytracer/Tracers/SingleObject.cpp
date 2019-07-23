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
		HitRecord hr;
		const std::vector<Object*>& objects = m_Renderer->GetObjects();

		IRAD_CORE_ASSERT(objects.empty() == false, "Scene Objects are empty");
		if (objects.back()->Hit(_ray, t, hr))
			hr.color = objects.back()->GetColor();

		if (hr.hasHit)
			return hr.color;
		else
			return m_Renderer->GetBackColor();

	}

}