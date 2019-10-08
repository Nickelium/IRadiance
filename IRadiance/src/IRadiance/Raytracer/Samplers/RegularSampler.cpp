#include "pch.h"
#include "RegularSampler.h"

#include "IRadiance/Raytracer/Maths/Utilities.h"

namespace IRadiance
{
	RegularSampler::RegularSampler(int _nbSamples)
		: Sampler(_nbSamples)
	{
		Init();
	}

	void RegularSampler::GenerateSamples2D()
	{
		float n = (float)(int)sqrt(m_NumSamples);
		for (int s = 0; s < m_NumSets; s++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					m_Samples2D.push_back(Point2(j / n, i / n));
	}

}