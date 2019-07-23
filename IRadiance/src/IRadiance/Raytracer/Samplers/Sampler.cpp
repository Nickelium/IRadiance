#include "pch.h"
#include "Sampler.h"

#include "IRadiance/Raytracer/Maths/Utilities.h"

namespace IRadiance
{

	Sampler::Sampler(int _nbSamples)
		: m_NumSamples(_nbSamples),
		m_NumSets(1),
		m_Count(0),
		m_ShuffledIndices(0),
		m_Init(false)

	{
	}

	Point2 Sampler::SampleUnitSquare()
	{
		if (!m_Init)
		{
			GenerateSamples();
			m_Init = true;
		}

		if (m_Count % m_NumSamples == 0)
			m_Jump = (RandInt() % m_NumSets) * m_NumSamples;

		return m_Samples[m_Jump + m_Count++ % m_NumSamples];
	}

}