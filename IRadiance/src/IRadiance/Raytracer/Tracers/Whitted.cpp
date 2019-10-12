#include "pch.h"
#include "Whitted.h"

#include "IRadiance/Raytracer/Materials/Material.h"

namespace IRadiance
{

	Whitted::Whitted(Renderer* _renderer)
		: Tracer(_renderer)
	{
	}

	RGBSpectrum Whitted::RayTrace(const Ray& _ray, int _depth) const
	{
		if (m_Renderer->MaxDepth() < _depth)
			return BLACK;

		HitRecord hr = m_Renderer->GetCollisionHandler()->HitObjects(_ray);

		if (hr.hasHit)
		{
			hr.ray = _ray;
			hr.depth = _depth;
			return hr.material->Shading(hr);
		}
		else
			return m_Renderer->GetBackColor();
	}
}