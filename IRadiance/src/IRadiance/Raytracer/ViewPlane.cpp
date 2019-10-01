#include "pch.h"
#include "ViewPlane.h"

#include "Samplers/Sampler.h"

namespace IRadiance
{
	ViewPlane::ViewPlane(int _hRes, int _vRes)
		: m_HorRes(_hRes), m_VertRes(_vRes), 
		m_PixelSize(1.0f), 
		m_Sampler(nullptr)
	{
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