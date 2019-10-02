#include "pch.h"
#include "Phong.h"

#include "IRadiance/Raytracer/BRDF/Lambertian.h"
#include "IRadiance/Raytracer/BRDF/GlossySpecular.h"	

#include "IRadiance/Raytracer/Renderer.h"

namespace IRadiance
{
	Phong::Phong()
		: ambientBRDF(new Lambertian),
		diffuseBRDF(new Lambertian),
		glossySpecularBRDF(new GlossySpecular)
	{
	}

	RGBSpectrum Phong::Shading(HitRecord& _hr)
	{
		Vector wO = -_hr.ray.d;
		RGBSpectrum L;
		L = ambientBRDF->rho(_hr, wO) * _hr.renderer->GetScene()->GetAmbientLight()->L(_hr);
		for (const Light* light : _hr.renderer->GetScene()->GetLights())
		{
			Vector wI = light->GetDirection(_hr);
			float nCosWi = Dot(wI, _hr.normal);
			if(nCosWi > 0.0f)
				L += (diffuseBRDF->f(_hr, wO, wI) + glossySpecularBRDF->f(_hr, wO, wI))
					* light->L(_hr) * nCosWi;
		}

		return L;
	}

	void Phong::SetKa(float _ka)
	{
		ambientBRDF->SetKa(_ka);
	}

	void Phong::SetKd(float _kd)
	{
		diffuseBRDF->SetKd(_kd);
	}

	void Phong::SetCd(const RGBSpectrum& _c)
	{
		ambientBRDF->SetCd(_c);
		diffuseBRDF->SetCd(_c);
	}

	void Phong::SetKs(const RGBSpectrum& _ks)
	{
		glossySpecularBRDF->SetKs(_ks);
	}

	void Phong::SetExp(float _exp)
	{
		glossySpecularBRDF->SetExp(_exp);
	}

	void Phong::SetCs(const RGBSpectrum& _cs)
	{
		glossySpecularBRDF->SetCs(_cs);
	}

}