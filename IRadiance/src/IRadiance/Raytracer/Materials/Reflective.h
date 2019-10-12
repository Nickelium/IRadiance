#pragma once

#include "Phong.h"

namespace IRadiance
{
	class PerfectSpecular;
	class Reflective : public Phong
	{
	public:	
		Reflective();
		virtual RGBSpectrum Shading(HitRecord& _hr) override;
		virtual RGBSpectrum AreaLightShading(HitRecord& _hr) override;

		void SetKr(float _kr);
		void SetCr(const RGBSpectrum& _cr);
	private:
		PerfectSpecular* m_ReflectiveBRDF;
	};
}
