#pragma once

#include "ToneMapper.h"

namespace IRadiance
{
	class Overflower : public ToneMapper
	{
	public:
		virtual RGBSpectrum ToneMap(const RGBSpectrum& _c) const override
		{
			if (_c.r > 1.0f || _c.g > 1.0f || _c.b > 1.0f)
				return RED;
			return _c;
		}

	};
}
