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

	void Sampler::GenerateIndices()
	{
		m_ShuffledIndices.reserve(m_NumSamples * m_NumSets);
		std::vector<int> indices;

		for (int i = 0; i < m_NumSamples; ++i)
			indices.push_back(i);

		for (int i = 0; i < m_NumSets; ++i)
		{
			random_shuffle(indices.begin(), indices.end());
			for (int j = 0; j < m_NumSamples; ++j)
				m_ShuffledIndices.push_back(indices[j]);
		}
	}

	Point2 Sampler::SampleUnitSquare()
	{
		if (!m_Init)
		{
			GenerateSamples();
			GenerateIndices();
			m_Init = true;
		}

		if (m_Count % m_NumSamples == 0)
			m_Jump = (RandInt() % m_NumSets) * m_NumSamples;

		return m_Samples[m_Jump + m_ShuffledIndices[m_Jump + m_Count++ % m_NumSamples]];
	}

}