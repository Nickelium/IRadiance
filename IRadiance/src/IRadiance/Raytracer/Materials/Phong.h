#pragma once

#include "Material.h"

namespace IRadiance
{
	class Lambertian;
	class GlossySpecular;
	class Phong : public Material
	{
	public:
		Phong();
		virtual RGBSpectrum Shading(HitRecord& _hr) override;
		virtual RGBSpectrum WhittedShading(HitRecord& _hr) override;
		virtual RGBSpectrum AreaLightShading(HitRecord& _hr) override;
		virtual RGBSpectrum PathShading(HitRecord& _hr) override;
		virtual RGBSpectrum HybridPathShading(HitRecord& _hr) override;

		virtual void SetSampler(Sampler* /*_sampler*/) override {}

		void SetKa(float _ka);
		void SetKd(float _kd);
		void SetCd(const RGBSpectrum& _c);
		void SetKs(const RGBSpectrum& _ks);
		void SetExp(float _exp);
		void SetCs(const RGBSpectrum& _cs);
	private:
		Lambertian* ambientBRDF;
		Lambertian* diffuseBRDF;
		GlossySpecular* glossySpecularBRDF;
	};
}
