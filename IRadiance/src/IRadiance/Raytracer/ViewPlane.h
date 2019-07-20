#pragma once

namespace IRadiance
{
	class ViewPlane
	{
	public:
		int m_HorRes;
		int m_VertRes;

		float m_PixelSize;
		float m_Gamma;
		float m_InvGamma;

		ViewPlane(int _hRes = 100, int _vRes = 100);

		inline void SetGamma(float _gamma)
		{
			m_Gamma = _gamma;
			m_InvGamma = 1.0f / m_Gamma;
		}
	};
}
