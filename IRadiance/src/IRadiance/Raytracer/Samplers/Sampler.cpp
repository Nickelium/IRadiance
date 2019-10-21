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

	void Sampler::GenerateDiskSamples()
	{
		int size = static_cast<int>(m_Samples2D.size());
		float r, phi; // polar coordinates
		Point2 sp; // sample point on unit
		m_SamplesDisk.reserve(size);
		for (int j = 0; j < size; j++)
		{
			// map sample point to [-1, 1] [-1,1]
			sp.x = 2.0f * m_Samples2D[j].x - 1.0f;
			sp.y = 2.0f * m_Samples2D[j].y - 1.0f;
			if (sp.x > -sp.y)
			{ // sectors 1 and 2
				if (sp.x > sp.y)
				{ // sector 1
					r = sp.x;
					phi = sp.y / sp.x;
				}
				else
				{ // sector 2
					r = sp.y;
					phi = 2 - sp.x / sp.y;
				}
			}
			else
			{ // sectors 3 and 4
				if (sp.x < sp.y)
				{ // sector 3
					r = -sp.x;
					phi = 4 + sp.y / sp.x;
				}
				else
				{ // sector 4
					r = -sp.y;
					if (sp.y != 0.0f) // avoid division by zero
						phi = 6 - sp.x / sp.y;
					else
						phi = 0.0f;
				}
			}
			phi *= Constants::PI / 4.0f;
			m_SamplesDisk.push_back({ r * cos(phi), r * sin(phi) });
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

	Point2 Sampler::SamplesUnitDisk()
	{
		if (m_Count % m_NumSamples == 0)
			m_Jump = (RandInt() % m_NumSets) * m_NumSamples;

		return m_SamplesDisk[m_Jump + m_ShuffledIndices[m_Jump + m_Count++ % m_NumSamples]];
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
		GenerateDiskSamples();
	}

}