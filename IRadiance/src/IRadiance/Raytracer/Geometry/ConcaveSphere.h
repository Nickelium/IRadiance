#pragma once

#include "Sphere.h"

namespace IRadiance
{
	class ConcaveSphere : public Sphere
	{
	public:
		ConcaveSphere(float _radius);
		virtual Vector Normal(const Point3& _p) const override;
	};
}
