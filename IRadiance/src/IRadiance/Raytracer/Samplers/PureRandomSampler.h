#pragma once

#include "Sampler.h"

namespace IRadiance
{
	class PureRandomSampler : public Sampler
	{
	public:
		PureRandomSampler(int _nbSamples);
		virtual void GenerateSamples() {}
		virtual Point2 SampleUnitSquare() override;
	};
}
