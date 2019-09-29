#pragma once

#include "IRadiance/Raytracer/Renderer.h"

namespace IRadiance
{
	class Tracer
	{
	public:
		Tracer(Renderer* _renderer) : m_Renderer(_renderer) {}
		virtual RGBSpectrum RayTrace(const Ray& _ray, int _depth) const = 0;
		virtual RGBSpectrum RayTrace(const Ray& /*_ray*/, float& /*_tMin*/, int /*depth*/) const { return BLACK; };
	protected:
		Renderer* m_Renderer;
	};
}
