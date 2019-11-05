#include "pch.h"
#include "Transparent.h"

#include "IRadiance/Raytracer/BxDF/PerfectSpecular.h"
#include "IRadiance/Raytracer/BxDF/PerfectTransmitter.h"

#include "IRadiance/Raytracer/Renderer.h"
#include "IRadiance/Raytracer/Tracers/Tracer.h"

namespace IRadiance
{
	Transparent::Transparent()
		: reflectiveBRDF(new PerfectSpecular),
		refractiveBTDF(new PerfectTransmitter)
	{
	}

	RGBSpectrum Transparent::WhittedShading(HitRecord& _hr)
	{
		RGBSpectrum L = Phong::WhittedShading(_hr);

		Vector wO = -_hr.ray.d;
		Vector wI;
		float pdf;
		RGBSpectrum fr = reflectiveBRDF->Sample_f(_hr, wO, wI, pdf);
		Ray reflected;
		reflected.o = _hr.hitPoint;
		reflected.d = wI;

		/*if (refractiveBTDF->Tir(_hr))
			L += _hr.renderer->GetTracer()->RayTrace(reflected, _hr.depth + 1);
		else*/
		{
			Vector wT;
			RGBSpectrum ft = refractiveBTDF->Sample_f(_hr, wO, wT, pdf);
			Ray refracted;
			refracted.o = _hr.hitPoint;
			refracted.d = wT;

			L += fr * _hr.renderer->GetTracer()->RayTrace(reflected, _hr.depth + 1) * abs(Dot(wI, _hr.normal));
			L += ft * _hr.renderer->GetTracer()->RayTrace(refracted, _hr.depth + 1) * abs(Dot(wT, _hr.normal));
		}

		return L;
	}

	RGBSpectrum Transparent::AreaLightShading(HitRecord& _hr)
	{
		return Phong::AreaLightShading(_hr);
	}

	RGBSpectrum Transparent::PathShading(HitRecord& _hr)
	{
		const float stopProbablity = std::min(1.0f, 0.0625f * _hr.depth);
		if (RandUNorm() < stopProbablity)
			return AreaLightShading(_hr);
		float contributionFactor = 1.0f / (1.0f - stopProbablity);

		RGBSpectrum L;
		Vector wO = -_hr.ray.d;
		Vector wI;
		float pdf;
		RGBSpectrum fr = reflectiveBRDF->Sample_f(_hr, wO, wI, pdf);
		Ray reflected;
		reflected.o = _hr.hitPoint;
		reflected.d = wI;

		Vector wT;
		RGBSpectrum ft = refractiveBTDF->Sample_f(_hr, wO, wT, pdf);
		Ray refracted;
		refracted.o = _hr.hitPoint;
		refracted.d = wT;

		L += ((fr * _hr.renderer->GetTracer()->RayTrace(reflected, _hr.depth + 1) * abs(Dot(wI, _hr.normal))))  * contributionFactor;

		L += ((ft * _hr.renderer->GetTracer()->RayTrace(refracted, _hr.depth + 1) * abs(Dot(wT, _hr.normal))))  * contributionFactor;

		return L;
	}

	RGBSpectrum Transparent::HybridPathShading(HitRecord& _hr)
	{
		return AreaLightShading(_hr) + PathShading(_hr);
	}

	void Transparent::SetKr(float _kr)
	{
		reflectiveBRDF->SetKr(_kr);
	}

	void Transparent::SetCr(const RGBSpectrum& _cr)
	{
		reflectiveBRDF->SetCr(_cr);
	}

	void Transparent::SetCt(const RGBSpectrum& _ct)
	{
		refractiveBTDF->SetCt(_ct);
	}

	void Transparent::SetIOR(float _ior)
	{
		refractiveBTDF->SetIOR(_ior);
	}

}