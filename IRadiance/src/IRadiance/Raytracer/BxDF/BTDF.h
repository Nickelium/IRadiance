#pragma once

namespace IRadiance
{
	class BTDF
	{
	public:
		virtual RGBSpectrum f(const HitRecord& _hr, const Vector& wO, const Vector& wI) const = 0;
		virtual RGBSpectrum Sample_f(const HitRecord& _hr, const Vector& wO, Vector& wI, float& pdf) const = 0;
		virtual RGBSpectrum rho(const HitRecord& _hr, const Vector& wO) const = 0;
		virtual bool Tir(const HitRecord& _hr) const = 0;
	};
}
