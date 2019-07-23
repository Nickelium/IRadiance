#pragma once

#include "Sampler.h"

namespace IRadiance
{
	class NRookSampler : public Sampler
	{
	public:
		NRookSampler(int _nbSamples);
		virtual void GenerateSamples() override;
		
	private:
		void ShuffleX();
		void ShuffleY();
	};
}
