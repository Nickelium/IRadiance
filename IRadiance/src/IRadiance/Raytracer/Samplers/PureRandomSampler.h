#pragma once

#include "Sampler.h"

namespace IRadiance
{
	class PureRandomSampler : public Sampler
	{
	public:
		PureRandomSampler(int _nbSamples);
		virtual void GenerateSamples2D() {}
		//Point2 SampleUnitSquare() override; TODO REMOVE
	};
}
