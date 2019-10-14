#include "pch.h"
#include "PathTracer.h"

#include "IRadiance/Raytracer/Materials/Material.h"

namespace IRadiance
{
	PathTracer::PathTracer(Renderer* _renderer)
		: Tracer(_renderer)
	{
	}

	RGBSpectrum PathTracer::RayTrace(const Ray& _ray, int _depth) const
	{
		if (_depth > m_Renderer->MaxDepth())
			return BLACK;

		HitRecord hr = m_Renderer->GetCollisionHandler()->HitObjects(_ray);

		if (hr.hasHit)
		{
			hr.ray = _ray;
			hr.depth = _depth;
			return hr.material->PathShading(hr);
		}
		else
			return m_Renderer->GetBackColor();
	}
}