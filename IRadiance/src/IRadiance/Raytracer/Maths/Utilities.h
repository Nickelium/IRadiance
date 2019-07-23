#pragma once

namespace IRadiance
{
	inline float Clamp(float _v, float _min, float _max)
	{
		return std::max(_min, std::min(_max, _v));
	}

	inline int RandInt()
	{
		return rand();
	}

	inline float Rand(float _min, float _max)
	{
		return (float(rand()) / RAND_MAX) * (_max - _min) + _min;
	}

	inline float RandUNorm()
	{
		return Rand(0.0f, 1.0f);
	}


	inline float RandSNorm()
	{
		return Rand(-1.0f, 1.0f);
	}
}
