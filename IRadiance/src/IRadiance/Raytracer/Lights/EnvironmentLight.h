#pragma once

#include "Light.h"

namespace IRadiance
{
	class Sampler;
	class Material;
	class EnvironmentLight : public Light
	{
	public:
		virtual Vector GetDirection(HitRecord& _hr) const override;
		virtual RGBSpectrum L(HitRecord& _hr) const override;
		virtual bool InShadow(const Ray&, const HitRecord&) const override;
		virtual float pdf(const HitRecord&) const override;

		void SetSampler(Sampler** _sampler);
		void SetMaterial(Material* _material);
	private:
		Sampler** m_Sampler;
		Material* m_Material; //Needs material because doesn't hold and object (assumes a sphere)
		mutable Vector u, v, w;
		mutable Vector wI;
	};
}
