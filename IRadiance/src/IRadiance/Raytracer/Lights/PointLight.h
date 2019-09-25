#pragma once

#include "Light.h"

namespace IRadiance
{
	class PointLight : public Light
	{
	public:
		virtual Vector GetDirection(HitRecord& _hr) override;
		virtual RGBSpectrum L(HitRecord& _hr) override;
	private:
		float ls;
		RGBSpectrum c;

		Point3 position;
	};
}
