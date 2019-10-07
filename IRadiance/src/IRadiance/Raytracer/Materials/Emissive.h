#pragma once

#include "Material.h"

namespace IRadiance
{
	class Emissive : public Material
	{
	public:	
		virtual RGBSpectrum Shading(HitRecord& _hr) override;
		virtual RGBSpectrum AreaLightShading(HitRecord& _hr) override;

		void SetLs(float _ls);
		void SetCe(const RGBSpectrum& _ce);

		virtual RGBSpectrum Le() const override;
	private:
		float ls;
		RGBSpectrum ce;
	};
}