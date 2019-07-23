#pragma once

#include "IRadiance/Raytracer/Maths/Point2.h"

namespace IRadiance
{
	class Sampler
	{
	public:
		Sampler(int _nbSamples);

		virtual void GenerateSamples() = 0;

		void SetupShuffledIndices();
		void Shuffle_samples();
		Point2 SampleUnitSquare();

		inline int GetNumberSamples() const { return m_NumSamples; }
		inline int GetNumberSets() const { return m_NumSets; }

	protected:
		int m_NumSamples; 
		int m_NumSets; 

		std::vector<Point2> m_Samples;
		std::vector<int> m_ShuffledIndices; 
		unsigned long m_Count;
		int m_Jump; 

		bool m_Init;
	};
}