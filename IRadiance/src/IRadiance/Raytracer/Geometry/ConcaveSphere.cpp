#include "pch.h"
#include "ConcaveSphere.h"

namespace IRadiance
{
	ConcaveSphere::ConcaveSphere(float _radius)
		: Sphere({}, _radius)
	{
	}

	Vector ConcaveSphere::Normal(const Point3& _p) const
	{
		return -Sphere::Normal(_p);
	}

}