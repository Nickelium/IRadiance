#include "pch.h"
#include "Sampler.h"

#include "IRadiance/Raytracer/Maths/Utilities.h"

namespace IRadiance
{
	Sampler::Sampler(int _nbSamples)
		: m_NumSamples(_nbSamples),
		m_NumSets(100),
		m_Count(0),
		m_ShuffledIndices(0),
		m_Init(false)

	{
		GenerateIndices();
	}

	void Sampler::GenerateSamples3D(float _e)
	{
		using namespace Constants;
		const int size = m_NumSamples * m_NumSets;
		m_Samples3D.reserve(size);
		for (int i = 0; i < size; ++i)
		{
			float cosTheta = pow(1.0f - m_Samples2D[i].y, 1 / (_e + 1));
			float sinTheta = sqrtf(1.0f - cosTheta * cosTheta);
			float cosPhi = cos(TwoPi * m_Samples2D[i].x);
			float sinPhi = sin(TwoPi * m_Samples2D[i].x);

			float x = sinTheta * cosPhi;
			float y = sinTheta * sinPhi;
			float z = cosTheta;

			m_Samples3D.push_back(Point3{x, y, z});
		}
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
		if (m_Count % m_NumSamples == 0)
			m_Jump = (RandInt() % m_NumSets) * m_NumSamples;

		return m_Samples2D[m_Jump + m_ShuffledIndices[m_Jump + m_Count++ % m_NumSamples]];
	}

	Point3 Sampler::SampleHemisphere()
	{
		if (m_Count % m_NumSamples == 0)
			m_Jump = (RandInt() % m_NumSets) * m_NumSamples;

		return m_Samples3D[m_Jump + m_ShuffledIndices[m_Jump + m_Count++ % m_NumSamples]];
	}

	void Sampler::Init()
	{
		GenerateSamples2D();
		GenerateSamples3D(1);
	}

}