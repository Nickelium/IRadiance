#pragma once

#include "Sampler.h"

namespace IRadiance
{
	class JitteredSampler : public Sampler
	{
	public:
		JitteredSampler(int _nbSamples);
		virtual void GenerateSamples2D() override;

	};
}
