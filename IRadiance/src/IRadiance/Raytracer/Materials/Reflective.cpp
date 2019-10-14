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

	RGBSpectrum Reflective::AreaLightShading(HitRecord& _hr)
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

	RGBSpectrum Reflective::PathShading(HitRecord& _hr)
	{
		Vector wO = -_hr.ray.d;
		Vector wI;
		float pdf;
		RGBSpectrum f = m_ReflectiveBRDF->Sample_f(_hr, wO, wI, pdf);
		Ray reflected;
		reflected.o = _hr.hitPoint;
		reflected.d = wI;
		float nCosWi = Dot(_hr.normal, wI);
		return (f * _hr.renderer->GetTracer()->RayTrace(reflected, _hr.depth + 1) * nCosWi) / pdf;
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