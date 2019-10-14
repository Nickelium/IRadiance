#pragma once

#include "Tracer.h"

namespace IRadiance
{
	class HybridPathTracer : public Tracer
	{
	public:
		HybridPathTracer(Renderer* _renderer);
		virtual RGBSpectrum RayTrace(const Ray& _ray, int _depth) const override;

	private:
	};
}
