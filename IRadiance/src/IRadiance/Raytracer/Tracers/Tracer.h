#pragma once

#include "IRadiance/Raytracer/Renderer.h"

namespace IRadiance
{
	class Tracer
	{
	public:
		virtual RGBSpectrum RayTrace(const Ray& _ray, int _depth) = 0;
	};
}
