#pragma once

#include "Light.h"

namespace IRadiance
{
	class Object;
	class AreaLight : public Light
	{
	public:
		virtual Vector GetDirection(HitRecord& _hr) const override;
		virtual RGBSpectrum L(HitRecord& _hr) const override;
		virtual bool InShadow(const Ray&, const HitRecord&) const override;
		virtual float G(const HitRecord&) const override;
		virtual float pdf(const HitRecord&) const override;

		void SetObject(Object* _object);

	private:
		Object* m_Object;
		mutable Point3 samplePoint;
		mutable Vector normal;
		mutable Vector wI;
	};
}
