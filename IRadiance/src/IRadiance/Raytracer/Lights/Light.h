#pragma once

namespace IRadiance
{
	class Light
	{
	public:
		virtual Vector GetDirection(HitRecord& _hr) const = 0;
		virtual RGBSpectrum L(HitRecord& _hr) const = 0; //Get Radiance
	protected:
		bool m_Shadows;
	};
}
