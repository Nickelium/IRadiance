#pragma once

#include "Material.h"

namespace IRadiance
{
	class Emissive : public Material
	{
	public:	
		virtual RGBSpectrum Shading(HitRecord& _hr) override;
		virtual RGBSpectrum WhittedShading(HitRecord& _hr) override;
		virtual RGBSpectrum AreaLightShading(HitRecord& _hr) override;
		virtual RGBSpectrum PathShading(HitRecord& _hr) override;
		virtual RGBSpectrum HybridPathShading(HitRecord& _hr) override;

		virtual void SetSampler(Sampler* /*_sampler*/) override {}

		void SetLs(float _ls);
		void SetCe(const RGBSpectrum& _ce);

		virtual RGBSpectrum Le() const override;
	private:
		float ls;
		RGBSpectrum ce;
	};
}