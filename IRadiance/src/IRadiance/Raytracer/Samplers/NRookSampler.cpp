#include "pch.h"
#include "NRookSampler.h"

#include "IRadiance/Raytracer/Maths/Utilities.h"

namespace IRadiance
{
	NRookSampler::NRookSampler(int _nbSamples)
		: Sampler(_nbSamples)
	{
		Init();
	}

	void NRookSampler::GenerateSamples2D()
	{
		for (int s = 0; s < m_NumSets; s++)
			for (int i = 0; i < m_NumSamples; i++)
				m_Samples2D.push_back(Point2(
					(i + RandUNorm()) / m_NumSamples,
					(i + RandUNorm()) / m_NumSamples));
		ShuffleX();
		ShuffleY();
	
	}

	void NRookSampler::ShuffleX()
	{
		for (int s = 0; s < m_NumSets; s++)
			for (int i = 0; i < m_NumSamples; i++)
			{
				int target = RandInt() % m_NumSamples + s * m_NumSamples;
				float tmp = m_Samples2D[i + s * m_NumSamples].x;
				m_Samples2D[i + s * m_NumSamples].x = m_Samples2D[target].x;
				m_Samples2D[target].x = tmp;
			}
	}

	void NRookSampler::ShuffleY()
	{
		for (int s = 0; s < m_NumSets; s++)
			for (int i = 0; i < m_NumSamples; i++)
			{
				int target = RandInt() % m_NumSamples + s * m_NumSamples;
				float tmp = m_Samples2D[i + s * m_NumSamples].y;
				m_Samples2D[i + s * m_NumSamples].x = m_Samples2D[target].y;
				m_Samples2D[target].y = tmp;
			}
	}

}