#pragma once

#include "Phong.h"

namespace IRadiance
{
	class PerfectSpecular;
	class PerfectTransmitter;
	class Transparent : public Phong
	{
	public:
		Transparent();
		virtual RGBSpectrum WhittedShading(HitRecord& _hr) override;
		virtual RGBSpectrum AreaLightShading(HitRecord& _hr) override;
		virtual RGBSpectrum PathShading(HitRecord& _hr) override;
		virtual RGBSpectrum HybridPathShading(HitRecord& _hr) override;

		//Reflective attributes
		void SetKr(float _kr);
		void SetCr(const RGBSpectrum& _cr);

		//Refractive
		void SetCt(const RGBSpectrum& _ct);
		void SetIOR(float _ior);


	private:
		PerfectSpecular* reflectiveBRDF;
		PerfectTransmitter* refractiveBTDF;
	};
}
