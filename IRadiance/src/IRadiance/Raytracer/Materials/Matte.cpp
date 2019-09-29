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
			//IRAD_CORE_INFO("{0}", cosNwI);
			if (cosNwI > 0.0f)
				L += diffuseBRDF->f(_hr, wO, wI) * light->L(_hr) * cosNwI;
		}
		return L;

	}

}