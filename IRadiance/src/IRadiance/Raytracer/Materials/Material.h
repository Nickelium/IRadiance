#pragma once

namespace IRadiance
{
	class Sampler;
	class Material 
	{
	public:
		virtual RGBSpectrum Le() const { return BLACK; }

		//TODO for pathtracing
		virtual RGBSpectrum RayCastShading(HitRecord& /*_hr*/) { return BLACK; }
		virtual RGBSpectrum WhittedShading(HitRecord& /*_hr*/) { return BLACK; }
		virtual RGBSpectrum AreaLightShading(HitRecord& /*_hr*/) { return BLACK; }
		virtual RGBSpectrum PathShading(HitRecord& /*_hr*/) { return BLACK; }
		virtual RGBSpectrum HybridPathShading(HitRecord& /*_hr*/) { return BLACK; }

		virtual RGBSpectrum Shading(HitRecord& _hr) = 0;

		virtual void SetSampler(Sampler* _sampler) = 0;
	};
}
