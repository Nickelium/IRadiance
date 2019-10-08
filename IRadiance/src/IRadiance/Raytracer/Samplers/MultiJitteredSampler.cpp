#include "pch.h"
#include "MultiJitteredSampler.h"

#include "IRadiance/Raytracer/Maths/Utilities.h"

namespace IRadiance
{
	MultiJitteredSampler::MultiJitteredSampler(int _nbSamples)
		: Sampler(_nbSamples)
	{
		Init();
	}

	void MultiJitteredSampler::GenerateSamples2D()
	{
		for (int s = 0; s < m_NumSets; s++)
			for (int i = 0; i < m_NumSamples; i++)
				m_Samples2D.push_back(Point2());

		int n = (int)sqrt(m_NumSamples);
		float subCellWidth = 1.0f / m_NumSamples;
		for (int s = 0; s < m_NumSets; ++s)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
				{
					m_Samples2D[i * n + j + s * m_NumSamples].x = 
						(i * n + j) * subCellWidth + Rand(0.0f, subCellWidth);
					m_Samples2D[i * n + j + s * m_NumSamples].y =
						(j * n + i) * subCellWidth + Rand(0.0f, subCellWidth);
				}
		ShuffleX();
		ShuffleY();

	}

	void MultiJitteredSampler::ShuffleX()
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

	void MultiJitteredSampler::ShuffleY()
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