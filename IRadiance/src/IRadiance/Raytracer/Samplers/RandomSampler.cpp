#include "pch.h"
#include "RandomSampler.h"

#include "IRadiance/Raytracer/Maths/Utilities.h"

namespace IRadiance
{
	RandomSampler::RandomSampler(int _nbSamples)
		: Sampler(_nbSamples)
	{
		Init();
	}

	void RandomSampler::GenerateSamples2D()
	{
		for (int s = 0; s < m_NumSets; s++)
		{
			for (int i = 0; i < m_NumSamples; i++)
			{
				m_Samples2D.push_back(Point2(RandUNorm(), RandUNorm()));
			}
		}
	}

}