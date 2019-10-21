#include "pch.h"
#include "Reflective.h"

#include "IRadiance/Raytracer/BRDF/PerfectSpecular.h"
#include "IRadiance/Raytracer/Renderer.h"
#include "IRadiance/Raytracer/Tracers/Tracer.h"

namespace IRadiance
{
	Reflective::Reflective()
		: m_ReflectiveBRDF(new PerfectSpecular)
	{
	}

	RGBSpectrum Reflective::Shading(HitRecord& _hr)
	{
		RGBSpectrum L = Phong::Shading(_hr); //Direct illumination
		Vector wO = -_hr.ray.d;
		Vector wI;
		float pdf;
		RGBSpectrum fr = m_ReflectiveBRDF->Sample_f(_hr, wO, wI, pdf);

		Ray reflected;
		reflected.o = _hr.hitPoint;
		reflected.d = wI;

		L += fr * _hr.renderer->GetTracer()->RayTrace(reflected, _hr.depth + 1) * Dot(wI, _hr.normal);

		return L;
	}

	RGBSpectrum Reflective::WhittedShading(HitRecord& _hr)
	{
		RGBSpectrum L = Phong::AreaLightShading(_hr); //Direct illumination
		Vector wO = -_hr.ray.d;
		Vector wI;
		float pdf;
		RGBSpectrum fr = m_ReflectiveBRDF->Sample_f(_hr, wO, wI, pdf);

		Ray reflected;
		reflected.o = _hr.hitPoint;
		reflected.d = wI;

		L += fr * _hr.renderer->GetTracer()->RayTrace(reflected, _hr.depth + 1) * Dot(wI, _hr.normal);

		return L;
	}

	RGBSpectrum Reflective::AreaLightShading(HitRecord& _hr)
	{
		return Phong::AreaLightShading(_hr);
	}

	RGBSpectrum Reflective::PathShading(HitRecord& _hr)
	{
		const float stopProbablity = std::min(1.0f, 0.0625f * _hr.depth);
		if (RandUNorm() < stopProbablity)
			return AreaLightShading(_hr);
		float contributionFactor = 1.0f / (1.0f - stopProbablity);
		contributionFactor = 1.0f;

		Vector wO = -_hr.ray.d;
		Vector wI;
		float pdf;
		RGBSpectrum f = m_ReflectiveBRDF->Sample_f(_hr, wO, wI, pdf);
		Ray reflected;
		reflected.o = _hr.hitPoint;
		reflected.d = wI;
		float nCosWi = Dot(_hr.normal, wI);
		return ((f * _hr.renderer->GetTracer()->RayTrace(reflected, _hr.depth + 1) * nCosWi)) 
			* contributionFactor;
	}

	RGBSpectrum Reflective::HybridPathShading(HitRecord& _hr)
	{
		return AreaLightShading(_hr) + PathShading(_hr);
	}

	void Reflective::SetKr(float _kr)
	{
		m_ReflectiveBRDF->SetKr(_kr);
	}

	void Reflective::SetCr(const RGBSpectrum& _cr)
	{
		m_ReflectiveBRDF->SetCr(_cr);
	}

}