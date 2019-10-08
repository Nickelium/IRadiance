#pragma once

#include "IRadiance/Raytracer/Maths/Ray.h"
#include "IRadiance/Raytracer/RGBSpectrum.h"
#include "HitRecord.h"

#include "IRadiance/Raytracer/Samplers/Sampler.h"

namespace IRadiance
{
	class Object
	{
	public:

		virtual bool Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const = 0;
		virtual bool ShadowHit(const Ray& /*_ray*/, float& /*_t*/) const = 0;

		void SetShadow(bool _shadow) { m_Shadow = _shadow; }
		bool CastShadow() const { return m_Shadow; }

		void SetMaterial(Material* _material) { material = _material; }
		Material* GetMaterial() const { return material; }

		void SetSampler(Sampler* _sampler) { m_Sampler = _sampler; }

		virtual Point3 Sample() const { return {}; }
		virtual float pdf(const HitRecord& /*_hr*/) const { return 1.0f; }
		virtual Vector Normal(const Point3& /*_p*/) const { return {}; }

	protected:
		Material* material;
		bool m_Shadow = true;

		//For object sampling
		Sampler* m_Sampler = nullptr;
	};

}
