#pragma once

#include "Material.h"

namespace IRadiance
{
	class Lambertian;
	class Matte : public Material
	{
	public:
		Matte();
		void SetKa(float _ka);
		void SetKd(float _kd);
		void SetCd(const RGBSpectrum& _c);

		virtual RGBSpectrum Shading(HitRecord& _hr) override;
		virtual RGBSpectrum WhittedShading(HitRecord& _hr) override;
		virtual RGBSpectrum AreaLightShading(HitRecord& _hr) override;
		virtual RGBSpectrum PathShading(HitRecord& _hr) override;
		virtual RGBSpectrum HybridPathShading(HitRecord& _hr) override;

		virtual void SetSampler(Sampler** _sampler) override;

	private:
		Lambertian* ambientBRDF;
		Lambertian* diffuseBRDF;
	};
}
