#include "pch.h"
#include "PureRandomSampler.h"
#include "IRadiance/Raytracer/Maths/Utilities.h"

namespace IRadiance
{
	PureRandomSampler::PureRandomSampler(int _nbSamples)
		: Sampler(_nbSamples)
	{
		//Init();
	}

	//TODO REMOVE

	//IRadiance::Point2 PureRandomSampler::SampleUnitSquare()
	//{
	//	return Point2(RandUNorm(), RandUNorm());
	//}

}