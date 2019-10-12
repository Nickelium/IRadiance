#pragma once

#include "IRadiance/Raytracer/Samplers/Sampler.h"

namespace IRadiance
{
	class BRDF
	{
	public:
		virtual RGBSpectrum f(const HitRecord& _hr, const Vector& wO, const Vector& wI) const = 0;
		/**
		 * For delta functions
		 */
		virtual RGBSpectrum Sample_f(const HitRecord& _hr, const Vector& wO, Vector& wI) const = 0;
		virtual RGBSpectrum rho(const HitRecord& _hr, const Vector& wO) const = 0;
	protected:
		Sampler* m_Sampler;
	};
}
