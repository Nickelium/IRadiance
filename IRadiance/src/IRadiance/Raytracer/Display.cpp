#include "pch.h"
#include "Display.h"

namespace IRadiance
{
	Display::Display(float _gamma)
			: m_Gamma(_gamma), m_InvGamma(1.0f / m_Gamma)
		{}

	void Display::SetGamma(float _gamma)
	{
		m_Gamma = _gamma;
		m_InvGamma = 1.0f / m_Gamma;
	}

	float Display::GetGamma() const
	{
		return m_Gamma;
	}

	float Display::GetInverseGamma() const
	{
		return m_InvGamma;
	}

	RGBA Display::ConvertDisplay(const RGBSpectrum& _c) const
	{
		return ToRGBA(Pow(_c, m_InvGamma));
	}

	RGBA ToRGBA(const RGBSpectrum& _c)
	{
		return RGBA
		{
			uint8_t(std::min(std::max(std::round(_c.r * 255.0f), 0.0f), 255.0f)),
			uint8_t(std::min(std::max(std::round(_c.g * 255.0f), 0.0f), 255.0f)),
			uint8_t(std::min(std::max(std::round(_c.b * 255.0f), 0.0f), 255.0f)),
			255
		};
	}

}