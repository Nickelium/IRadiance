#pragma once

#include "IRadiance/Raytracer/Maths/Point.h"
#include "IRadiance/Raytracer/Maths/Normal.h"

#include "IRadiance/Raytracer/RGBSpectrum.h"

namespace IRadiance
{
	struct HitRecord
	{
		bool hasHit = false;
		Point hitPoint = {};
		Normal normal = {};
		float t = std::numeric_limits<float>::max();
		RGBSpectrum color = BLACK;
	};
}