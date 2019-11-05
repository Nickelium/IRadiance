#include "pch.h"
#include "Phong.h"

#include "IRadiance/Raytracer/BxDF/Lambertian.h"
#include "IRadiance/Raytracer/BxDF/GlossySpecular.h"	

#include "IRadiance/Raytracer/Renderer.h"
#include "IRadiance/Raytracer/Tracers/Tracer.h"

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
			if (nCosWi > 0.0f)
			{
				bool inShadow = false;	

				if (light->CastShadow())
				{
					Ray shadowRay;
					shadowRay.o = _hr.hitPoint;
					shadowRay.d = wI;
					inShadow = light->InShadow(shadowRay, _hr);
				}

				if(!inShadow)
					L += (diffuseBRDF->f(_hr, wO, wI) + glossySpecularBRDF->f(_hr, wO, wI))
						* light->L(_hr) * nCosWi;
			}
		}

		return L;
	}

	RGBSpectrum Phong::WhittedShading(HitRecord& _hr)
	{
		return Phong::AreaLightShading(_hr);
	}

	RGBSpectrum Phong::AreaLightShading(HitRecord& _hr)
	{
		Vector wO = -_hr.ray.d;
		RGBSpectrum L = _hr.renderer->GetScene()->GetAmbientLight()->L(_hr) * ambientBRDF->rho(_hr, wO);
		const auto& lights = _hr.renderer->GetScene()->GetLights();
		for (auto light : lights)
		{
			const int shadowRays = 1;
			for (int i = 0; i < shadowRays; ++i)
			{
				Vector wI = light->GetDirection(_hr);
				float nCosWi = Dot(_hr.normal, wI);
				if (nCosWi > 0.0f)
				{
					bool inShadow = false;
					if (light->CastShadow())
					{
						Ray shadowRay;
						shadowRay.o = _hr.hitPoint;
						shadowRay.d = wI;
						inShadow = light->InShadow(shadowRay, _hr);
					}
					if (!inShadow)
						L +=
						((diffuseBRDF->f(_hr, wO, wI) + glossySpecularBRDF->f(_hr, wO, wI)) *
							light->L(_hr) * light->G(_hr) * nCosWi) / light->pdf(_hr);
				}
			}
			L /= shadowRays;
		}

		return L;
	}

	RGBSpectrum Phong::PathShading(HitRecord& _hr)
	{
		Vector wO = -_hr.ray.d;
		Vector wI;
		float pdf;
		RGBSpectrum f = glossySpecularBRDF->Sample_f(_hr, wO, wI, pdf);
		float nCosWi = Dot(_hr.normal, wI);
		Ray reflected;
		reflected.o = _hr.hitPoint;
		reflected.d = wI;

		return ((f * _hr.renderer->GetTracer()->RayTrace(reflected, _hr.depth + 1) * nCosWi) / pdf);
	}

	RGBSpectrum Phong::HybridPathShading(HitRecord& _hr)
	{
		return PathShading(_hr);
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