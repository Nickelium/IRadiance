#pragma once

#define BLACK RGBSpectrum(0.0f, 0.0f, 0.0f)
#define WHITE RGBSpectrum(1.0f, 1.0f, 1.0f)
#define RED	RGBSpectrum(1.0f, 0.0f, 0.0f)
#define GREEN RGBSpectrum(0.0f, 1.0f, 0.0f)
#define BLUE RGBSpectrum(0.0f, 0.0f, 1.0f)

#include "IRadiance/Framework/Renderer/ImageBuffer.h"

namespace IRadiance
{
	class RGBSpectrum
	{
	public:
		float r, g, b;

		RGBSpectrum(float _val = 1.0f);
		RGBSpectrum(float _r, float _g, float _b);
		RGBSpectrum(const RGBSpectrum& _other);

		RGBSpectrum& operator=(const RGBSpectrum& _other);

		RGBSpectrum& operator+=(const RGBSpectrum& _c);
		RGBSpectrum& operator-=(const RGBSpectrum& _c);
		RGBSpectrum& operator*=(float _f);
		RGBSpectrum& operator/=(float _f);

	};

	RGBSpectrum operator+(const RGBSpectrum& _c1, const RGBSpectrum& _c2);
	RGBSpectrum operator-(const RGBSpectrum& _c1, const RGBSpectrum& _c2);
	RGBSpectrum operator*(const RGBSpectrum& _c, float _f);
	RGBSpectrum operator*(float _f, const RGBSpectrum& _c);
	RGBSpectrum operator*(const RGBSpectrum& _c1, const RGBSpectrum& _c2);
	RGBSpectrum operator/(const RGBSpectrum& _c, float _f);

	RGBSpectrum Clamp(const RGBSpectrum& _c, float _min, float _max);
	RGBSpectrum Pow(const RGBSpectrum& _c, float _f);
	float Average(const RGBSpectrum& _c);
}
