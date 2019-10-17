#include "pch.h"
#include "HybridPathTracer.h"

#include "IRadiance/Raytracer/Materials/Material.h"

namespace IRadiance
{

	HybridPathTracer::HybridPathTracer(Renderer* _renderer)
		: Tracer(_renderer)
	{
	}

	RGBSpectrum HybridPathTracer::RayTrace(const Ray& _ray, int _depth) const
	{
		HitRecord hr = m_Renderer->GetCollisionHandler()->HitObjects(_ray);
		if (hr.hasHit)
		{
			hr.ray = _ray;
			hr.depth = _depth;

			//RGBSpectrum L;
			//if (hr.depth == 0)
			//	L = hr.material->AreaLightShading(hr);
			return hr.material->HybridPathShading(hr);
		}
		return m_Renderer->GetBackColor();
	}

}