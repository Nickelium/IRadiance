#pragma once

namespace IRadiance
{
	class Display
	{
	public:
		Display(float _gamma);
		void SetGamma(float _gamma);
		float GetGamma() const;
		float GetInverseGamma() const;

		RGBSpectrum ConvertDisplay(const RGBSpectrum& _c);
	private:
		float m_Gamma;
		float m_InvGamma;
	};
}
