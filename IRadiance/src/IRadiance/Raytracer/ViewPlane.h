#pragma once

namespace IRadiance
{
	class Sampler;

	class ViewPlane
	{
	public:
		int m_HorRes;
		int m_VertRes;

		float m_PixelSize;

		int m_NumSamples;

		ViewPlane(int _hRes = 100, int _vRes = 100);

		void SetSampler(Sampler** _sampler);

		inline Sampler** GetSampler() const { return m_Sampler; }

	private: 
		Sampler** m_Sampler;
	};
}
