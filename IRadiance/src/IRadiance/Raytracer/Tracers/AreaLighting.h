#pragma once
#include "Tracer.h"

namespace IRadiance
{
	class AreaLighting : public Tracer
	{
	public:
		AreaLighting(Renderer* _renderer);
		virtual RGBSpectrum RayTrace(const Ray& _ray, int _depth) const override;
	};
}
