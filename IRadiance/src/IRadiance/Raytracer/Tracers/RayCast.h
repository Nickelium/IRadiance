#pragma once

#include "Tracer.h"

namespace IRadiance
{
	class Renderer;
	class RayCast : public Tracer
	{
	public:
		RayCast(Renderer* _renderer);
		virtual RGBSpectrum RayTrace(const Ray& _ray, int _depth) const override;
	};
}
