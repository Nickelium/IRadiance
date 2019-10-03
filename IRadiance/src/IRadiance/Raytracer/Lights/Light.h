#pragma once

namespace IRadiance
{
	class Light
	{
	public:
		virtual Vector GetDirection(HitRecord& _hr) const = 0;
		virtual RGBSpectrum L(HitRecord& _hr) const = 0; //Get Radiance
		virtual bool InShadow(const Ray& /*_r*/, const HitRecord& /*_hr*/) const = 0;

		inline void SetShadow(bool _shadow) { m_Shadows = _shadow; }
		bool CastShadow() const { return m_Shadows; }
	protected:
		bool m_Shadows = true;
	};
}
