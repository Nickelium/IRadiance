#pragma once

namespace IRadiance
{
	class Sampler;
	class SamplerHandler
	{
	public:
		SamplerHandler();
		void SetNbSamples();
		Sampler** GetSampler();
	private:
		Sampler* m_Sampler;
	};
}
