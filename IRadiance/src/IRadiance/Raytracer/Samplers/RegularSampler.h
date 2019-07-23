#pragma once

#include "Sampler.h"

namespace IRadiance
{
	class RegularSampler : public Sampler
	{
	public:
		RegularSampler(int _nbSamples);
		virtual void GenerateSamples() override;

	};
}
