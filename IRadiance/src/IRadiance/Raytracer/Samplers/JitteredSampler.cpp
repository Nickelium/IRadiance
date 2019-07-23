#include "pch.h"
#include "JitteredSampler.h"

#include "IRadiance/Raytracer/Maths/Utilities.h"

namespace IRadiance
{

	JitteredSampler::JitteredSampler(int _nbSamples)
		: Sampler(_nbSamples)
	{

	}

	void JitteredSampler::GenerateSamples()
	{
		float n = (float)(int)sqrt(m_NumSamples);
		for (int s = 0; s < m_NumSets; ++s)
		{
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					m_Samples.push_back
					(
						Point2
						{
							(j + RandUNorm()) / n,
							(i + RandUNorm()) / n
						}
					);
				}
			}
		}
	}
}