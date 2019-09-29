#pragma once

namespace IRadiance
{
	class Material 
	{
	public:
		//TODO for pathtracing
		virtual RGBSpectrum RayCastShading(HitRecord& /*_hr*/) { return BLACK; };
		virtual RGBSpectrum WhittedShading(HitRecord& /*_hr*/) { return BLACK; };
		virtual RGBSpectrum AreaLightShading(HitRecord& /*_hr*/) { return BLACK; };
		virtual RGBSpectrum PathShading(HitRecord& /*_hr*/) { return BLACK; };

		virtual RGBSpectrum Shading(HitRecord& _hr) = 0;
	};
}
