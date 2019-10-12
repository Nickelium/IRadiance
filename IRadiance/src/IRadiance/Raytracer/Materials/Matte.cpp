#include "pch.h"
#include "Matte.h"

#include "IRadiance/Raytracer/BRDF/Lambertian.h"
#include "IRadiance/Raytracer/Renderer.h"

namespace IRadiance
{

	Matte::Matte()
		: ambientBRDF(new Lambertian),
		diffuseBRDF(new Lambertian)
	{

	}

	void Matte::SetKa(float _ka)
	{
		ambientBRDF->SetKa(_ka);
	}

	void Matte::SetKd(float _kd)
	{
		diffuseBRDF->SetKd(_kd);
	}

	void Matte::SetCd(const RGBSpectrum& _c)
	{
		ambientBRDF->SetCd(_c);
		diffuseBRDF->SetCd(_c);
	}

	RGBSpectrum Matte::Shading(HitRecord& _hr)
	{
		Vector wO = -_hr.ray.d;
		RGBSpectrum L = ambientBRDF->rho(_hr, wO) * _hr.renderer->GetScene()->GetAmbientLight()->L(_hr);
		auto lights = _hr.renderer->GetScene()->GetLights();
		for (auto light : lights)
		{
			Vector wI = light->GetDirection(_hr);
			float cosNwI = Dot(_hr.normal, wI);
			if (cosNwI > 0.0f)
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
					L += diffuseBRDF->f(_hr, wO, wI) * light->L(_hr) * cosNwI;
			}
		}
		return L;

	}

	RGBSpectrum Matte::AreaLightShading(HitRecord& _hr)
	{
		Vector wO = -_hr.ray.d;
		RGBSpectrum L = _hr.renderer->GetScene()->GetAmbientLight()->L(_hr) * ambientBRDF->rho(_hr, wO );
		const auto& lights = _hr.renderer->GetScene()->GetLights();
		for (auto light : lights)
		{
			const int nbShadowRays = 1;
			for (int i = 0; i < nbShadowRays; ++i)
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
						L += (diffuseBRDF->f(_hr, wO, wI) * light->L(_hr) *
							light->G(_hr) * nCosWi) / light->pdf(_hr);
				}
			}
			L /= nbShadowRays;
		}

		return L;
	}

}