#pragma once

#include "IRadiance/Raytracer/Maths/Point2.h"

namespace IRadiance
{
	class Sampler
	{
	public:
		Sampler(int _nbSamples);

		virtual void GenerateSamples2D() = 0;
		void GenerateSamples3D(float _e);
		void GenerateDiskSamples();

		void GenerateIndices();

		Point2 SampleUnitSquare();
		Point2 SamplesUnitDisk();
		Point3 SampleHemisphere();

		inline int GetNumberSamples() const { return m_NumSamples; }
		inline int GetNumberSets() const { return m_NumSets; }

		void Init();

	protected:
		int m_NumSamples; 
		int m_NumSets; 

		std::vector<Point2> m_Samples2D;
		std::vector<Point2> m_SamplesDisk;
		std::vector<Point3> m_Samples3D;

		std::vector<int> m_ShuffledIndices; 
		unsigned long m_Count;
		int m_Jump; 

		bool m_Init;
	};
}