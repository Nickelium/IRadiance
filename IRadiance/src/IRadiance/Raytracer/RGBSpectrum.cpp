#include "pch.h"
#include "RGBSpectrum.h"

namespace IRadiance
{
	RGBSpectrum::RGBSpectrum(float _val /*= 1.0f*/)
		: RGBSpectrum(_val, _val, _val)
	{
	}

	RGBSpectrum::RGBSpectrum(float _r, float _g, float _b)
		: r(_r), g(_g), b(_b)
	{
	}

	RGBSpectrum::RGBSpectrum(const RGBSpectrum& _other)
		: RGBSpectrum(_other.r, _other.g, _other.b)
	{
	}

	RGBSpectrum& RGBSpectrum::operator/=(float _f)
	{
		float invF = 1.0f / _f;
		r *= invF;
		g *= invF;
		b *= invF;
		return *this;
	}

	RGBSpectrum& RGBSpectrum::operator*=(float _f)
	{
		r *= _f;
		g *= _f;
		b *= _f;
		return *this;
	}

	RGBSpectrum& RGBSpectrum::operator-=(const RGBSpectrum& _c)
	{
		r -= _c.r;
		g -= _c.g;
		b -= _c.b;
		return *this;
	}

	RGBSpectrum& RGBSpectrum::operator+=(const RGBSpectrum& _c)
	{
		r += _c.r;
		g += _c.g;
		b += _c.b;
		return *this;
	}

	RGBSpectrum& RGBSpectrum::operator=(const RGBSpectrum& _other)
	{
		r = _other.r;
		g = _other.g;
		b = _other.b;
		return *this;
	}

	RGBSpectrum operator+(const RGBSpectrum& _c1, const RGBSpectrum& _c2)
	{
		RGBSpectrum c;
		c.r = _c1.r + _c2.r;
		c.g = _c1.g + _c2.g;
		c.b = _c1.b + _c2.b;
		return c;
	}

	RGBSpectrum operator-(const RGBSpectrum& _c1, const RGBSpectrum& _c2)
	{
		RGBSpectrum c;
		c.r = _c1.r - _c2.r;
		c.g = _c1.g - _c2.g;
		c.b = _c1.b - _c2.b;
		return c;
	}

	RGBSpectrum operator*(const RGBSpectrum& _c, float _f)
	{
		RGBSpectrum output;
		output.r = _c.r * _f;
		output.g = _c.g * _f;
		output.b = _c.b * _f;
		return output;
	}

	RGBSpectrum operator*(float _f, const RGBSpectrum& _c)
	{
		RGBSpectrum output;
		output.r = _f * _c.r;
		output.g = _f * _c.g;
		output.b = _f * _c.b;
		return output;
	}

	RGBSpectrum operator*(const RGBSpectrum& _c1, const RGBSpectrum& _c2)
	{
		RGBSpectrum output;
		output.r = _c1.r * _c2.r;
		output.g = _c1.g * _c2.g;
		output.b = _c1.b * _c2.b;
		return output;
	}

	RGBSpectrum operator/(const RGBSpectrum& _c, float _f)
	{
		RGBSpectrum output;
		float invF = 1.0f / _f;
		output.r = _c.r * invF;
		output.g = _c.g * invF;
		output.b = _c.b * invF;
		return output;
	}

	RGBSpectrum Clamp(const RGBSpectrum& _c, float _min, float _max)
	{
		RGBSpectrum color;
		color.r = std::min(std::max(_c.r, _min), _max);
		color.g = std::min(std::max(_c.g, _min), _max);
		color.b = std::min(std::max(_c.b, _min), _max);
		return color;
	}

	RGBSpectrum Pow(const RGBSpectrum& _c, float _f)
	{
		if (_f == 1.0f)
			return _c;

		RGBSpectrum output;
		output.r = pow(_c.r, _f);
		output.g = pow(_c.g, _f);
		output.b = pow(_c.b, _f);
		return output;
	}

	float Average(const RGBSpectrum& _c)
	{
		return 0.333333333f * (_c.r + _c.g + _c.b);
	}

	RGBA ToRGBA(const RGBSpectrum& _c)
	{
		return RGBA
		{
			uint8_t(std::min(std::max(std::round(_c.r * 255.0f), 0.0f), 255.0f)),
			uint8_t(std::min(std::max(std::round(_c.g * 255.0f), 0.0f), 255.0f)),
			uint8_t(std::min(std::max(std::round(_c.b * 255.0f), 0.0f), 255.0f)), 
			255
		};
	}

}