#include "pch.h"
#include "MultiObject.h"

#include "IRadiance/Raytracer/Maths/Utilities.h"

namespace IRadiance
{

	MultiObject::MultiObject(Renderer* _renderer)
		: Tracer(_renderer)
	{}

	RGBSpectrum MultiObject::RayTrace(const Ray& _ray, int /*_depth*/) const
	{
		HitRecord hr = m_Renderer->GetCollisionHandler()->HitObjects(_ray);

		if (hr.hasHit)
		{
			//IRAD_CORE_TRACE("{0}, {1}, {2} : normal", normal.x, normal.y, normal.z);
			//return 0.5f * (RGBSpectrum(normal.x, normal.y, normal.z) + RGBSpectrum{1, 1, 1});
			return RED;
		}
		else
			return m_Renderer->GetBackColor();
	}

}