#pragma once

#include "Tracer.h"

namespace IRadiance
{
	class SingleObject : public Tracer
	{
	public:
		SingleObject(Renderer* _renderer);

		virtual RGBSpectrum RayTrace(const Ray& _ray) override;
	private:
		Renderer* m_Renderer;
	};
}
