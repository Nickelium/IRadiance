#include "pch.h"
#include "ViewPlane.h"

#include "Samplers/Sampler.h"

namespace IRadiance
{
	ViewPlane::ViewPlane(int _hRes, int _vRes)
		: m_HorRes(_hRes), m_VertRes(_vRes), 
		m_PixelSize(1.0f), 
		m_Gamma(2.2f),
		m_InvGamma(1.0f / 2.2f), 
		m_Sampler(nullptr)
	{
	}

	void ViewPlane::SetGamma(float _gamma)
	{
		m_Gamma = _gamma;
		m_InvGamma = 1.0f / m_Gamma;
	}

	void ViewPlane::SetSampler(Sampler* _sampler)
	{
		if (m_Sampler)
		{
			delete m_Sampler;
			m_Sampler = nullptr;
		}
		m_Sampler = _sampler;
		m_NumSamples = m_Sampler->GetNumberSamples();
	}

}