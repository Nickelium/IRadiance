#pragma once

namespace IRadiance
{
	class ToneMapper
	{
	public:
		virtual RGBSpectrum ToneMap(const RGBSpectrum& _c) const = 0;
	};
}
