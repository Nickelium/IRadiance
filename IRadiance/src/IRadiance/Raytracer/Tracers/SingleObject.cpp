#include "pch.h"
#include "SingleObject.h"

namespace IRadiance
{
	SingleObject::SingleObject(Renderer* _renderer)
		: Tracer(_renderer)
	{}

	RGBSpectrum SingleObject::RayTrace(const Ray& _ray, int /*_depth*/) const
	{
		float t;
		HitRecord hr(m_Renderer);
		const auto& objects = m_Renderer->GetScene()->GetObjects();

		IRAD_CORE_ASSERT(objects.empty() == false, "Scene Objects are empty");
		objects.back()->Hit(_ray, t, hr);

		if (hr.hasHit)
			return RED;
		else
			return m_Renderer->GetBackColor();

	}

}