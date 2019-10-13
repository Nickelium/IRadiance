#pragma once

#include "Tracer.h"

namespace IRadiance
{
	class PathTrace : public Tracer
	{
	public:
		virtual RGBSpectrum RayTrace(const Ray& _ray, int _depth) const override;

	private:
	};
}
