#pragma once

#include "IRadiance/Raytracer/ToneMapper/ToneMapper.h"

namespace IRadiance
{
	class Clamper : public ToneMapper
	{
	public:
		virtual RGBSpectrum ToneMap(const RGBSpectrum& _c) const override
		{
			return Clamp(_c, 0.0f, 1.0f);
		}
	};
}
