#pragma once

#include "Sampler.h"

namespace IRadiance
{
	class MultiJitteredSampler : public Sampler
	{
	public:
		MultiJitteredSampler(int _nbSamples);
		virtual void GenerateSamples() override;
	private:
		void ShuffleX();
		void ShuffleY();
	};
}
