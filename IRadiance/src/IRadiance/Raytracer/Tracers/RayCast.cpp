#include "pch.h"
#include "RayCast.h"

#include "IRadiance/Raytracer/Materials/Material.h"

namespace IRadiance
{
	RayCast::RayCast(Renderer* _renderer)
		: Tracer(_renderer)
	{}

	RGBSpectrum RayCast::RayTrace(const Ray& _ray, int _depth) const
	{
		if (_depth < m_Renderer->MaxDepth())
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