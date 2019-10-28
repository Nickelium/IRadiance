#include "pch.h"
#include "GlossySpecular.h"

namespace IRadiance
{
	GlossySpecular::GlossySpecular(const RGBSpectrum& _ks /*= WHITE*/, float _exp /*= 1.0f*/,
		const RGBSpectrum& _cs)
		: ks(_ks), exp(_exp), cs(_cs)
	{
	}

	RGBSpectrum GlossySpecular::f(const HitRecord& _hr, const Vector& wO, const Vector& wI) const
	{
		RGBSpectrum f = BLACK;
		Vector r = -wI + 2.0f * Dot(wI, _hr.normal) * _hr.normal;
		float rcoswO = Dot(wO, r);
		if (rcoswO > 0.0f)
			f = ks * std::pow(rcoswO, exp);
		return f;
	}

	RGBSpectrum GlossySpecular::Sample_f(const HitRecord& /*_hr*/, const Vector& /*wO*/, Vector& /*wI*/, float& /*pdf*/) const
	{
		return BLACK;
	}

	RGBSpectrum GlossySpecular::rho(const HitRecord& /*_hr*/, const Vector& /*wO*/) const
	{
		return BLACK;
	}

	void GlossySpecular::SetKs(const RGBSpectrum& _ks)
	{
		ks = _ks;
	}

	void GlossySpecular::SetExp(float _exp)
	{
		exp = _exp;
	}

	void GlossySpecular::SetCs(const RGBSpectrum& _cs)
	{
		cs = _cs;
	}

}