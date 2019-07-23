#pragma once

namespace IRadiance
{
	inline float Clamp(float _v, float _min, float _max)
	{
		return std::max(_min, std::min(_max, _v));
	}
}
