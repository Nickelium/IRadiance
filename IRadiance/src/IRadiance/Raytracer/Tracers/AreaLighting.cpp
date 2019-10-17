#include "pch.h"
#include "AreaLighting.h"

#include "IRadiance/Raytracer/Materials/Material.h"

namespace IRadiance
{
	AreaLighting::AreaLighting(Renderer* _renderer)
		: Tracer(_renderer)
	{}

	RGBSpectrum AreaLighting::RayTrace(const Ray& _ray, int _depth) const
	{
		HitRecord hr = m_Renderer->GetCollisionHandler()->HitObjects(_ray);

		if (hr.hasHit)
		{
			hr.ray = _ray;
			hr.depth = _depth;
			return hr.material->AreaLightShading(hr);
		}
		else
			return m_Renderer->GetBackColor();
	}
}
