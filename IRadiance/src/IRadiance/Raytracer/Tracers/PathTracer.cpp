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

		HitRecord hr = m_Renderer->GetCollisionHandler()->HitObjects(_ray);

		if (hr.hasHit)
		{
			hr.ray = _ray;
			hr.depth = _depth;

			const float stopProbablity = std::min(1.0f, 0.0625f * _depth);
			if (RandUNorm() < stopProbablity)
				return hr.material->AreaLightShading(hr);
			float contributionFactor = 1.0f / (1.0f - stopProbablity);

			return hr.material->PathShading(hr) * contributionFactor;
		}
		else
			return m_Renderer->GetBackColor();
	}
}