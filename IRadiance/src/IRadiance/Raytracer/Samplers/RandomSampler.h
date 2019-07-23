#pragma once

#include "Sampler.h"

namespace IRadiance
{
	class RandomSampler : public Sampler
	{
	public:
		RandomSampler(int _nbSamples);
		virtual void GenerateSamples() override;

	};
}
