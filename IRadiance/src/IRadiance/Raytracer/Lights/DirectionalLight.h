#pragma once

#include "Light.h"

namespace IRadiance
{
	class DirectionalLight : public Light
	{
	public:
		virtual Vector GetDirection(HitRecord& _hr) override;
		virtual RGBSpectrum L(HitRecord& _hr) override;
	private:
		float ls;
		RGBSpectrum c;

		Vector direction;
	};
}
