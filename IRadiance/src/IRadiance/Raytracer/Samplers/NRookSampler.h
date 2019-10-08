#pragma once

#include "Sampler.h"

namespace IRadiance
{
	class NRookSampler : public Sampler
	{
	public:
		NRookSampler(int _nbSamples);
		virtual void GenerateSamples2D() override;
		
	private:
		void ShuffleX();
		void ShuffleY();
	};
}
