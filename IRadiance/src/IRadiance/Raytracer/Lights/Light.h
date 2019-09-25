#pragma once

namespace IRadiance
{
	class Light
	{
	public:
		virtual Vector GetDirection(HitRecord& _hr) = 0;
		virtual RGBSpectrum L(HitRecord& _hr) = 0; //Get Radiance
	protected:
		bool m_Shadows;
	};
}
