#pragma once

#include "Tracer.h"

namespace IRadiance
{
	class PathTracer : public Tracer
	{
	public:
		PathTracer(Renderer* _renderer);
		virtual RGBSpectrum RayTrace(const Ray& _ray, int _depth) const override;

	private:
	};
}
