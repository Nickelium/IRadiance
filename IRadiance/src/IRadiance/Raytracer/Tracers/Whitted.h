#pragma once

#include "Tracer.h"

namespace IRadiance
{
	class Whitted : public Tracer
	{
	public:
		Whitted(Renderer* _renderer);
		virtual RGBSpectrum RayTrace(const Ray& _ray, int _depth) const override;
	private:
	};
}
