#pragma once

#include "Tracer.h"

namespace IRadiance
{
	class MultiObject : public Tracer 
	{
	public:
		MultiObject(Renderer* _renderer);
		virtual RGBSpectrum RayTrace(const Ray& _ray, int _depth) override;
	private:
		Renderer* m_Renderer;
	};
}
