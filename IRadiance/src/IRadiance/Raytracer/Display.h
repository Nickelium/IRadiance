#pragma once

#include "IRadiance/Framework/Renderer/ImageBuffer.h"

namespace IRadiance
{
	class Display
	{
	public:
		Display(float _gamma = 1.0f);
		void SetGamma(float _gamma);
		float GetGamma() const;
		float GetInverseGamma() const;

		RGBA ConvertDisplay(const RGBSpectrum& _c) const;
	private:

		float m_Gamma;
		float m_InvGamma;
	};

	RGBA ToRGBA(const RGBSpectrum& _c);
}
