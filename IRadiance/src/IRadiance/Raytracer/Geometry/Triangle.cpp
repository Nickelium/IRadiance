#include "pch.h"
#include "Triangle.h"

namespace IRadiance
{
	const float Triangle::eps = 1e-3f;

	Triangle::Triangle(const Point3& _p0, const Point3& _p1, const Point3& _p2)
		: Triangle(_p0, _p1, _p2, Cross(_p1 - _p0, _p2 - _p0))
	{
	}

	Triangle::Triangle(const Point3& _p0, const Point3& _p1, const Point3& _p2, const Vector& _n)
		: p0(_p0), p1(_p1), p2(_p2), n(Normalize(_n)), 
		invArea(1.0f / (0.5f * Length(Cross(_p1 - _p0, _p2 - _p0))))
	{
	}

	bool Triangle::Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const
	{
		float a = p0.x - p1.x;
		float e = p0.y - p1.y;
		float i = p0.z - p1.z;

		float b = p0.x - p2.x;
		float f = p0.y - p2.y;
		float j = p0.z - p2.z;
		
		float c = _ray.d.x;
		float g = _ray.d.y;
		float k = _ray.d.z;
		
		float d = p0.x - _ray.o.x;
		float h = p0.y - _ray.o.y;
		float l = p0.z - _ray.o.z;

		float det = a * (f * k - g * j) + b * (g * i - e * k) + c * (e * j - f * i);
		if (abs(det) < 1e-3f)
			return false;

		float invDet = 1.0f / det;

		float beta = (d * (f * k - g * j) + b * (g * l - h * k) + c * (h * j - f * l)) * invDet;
		if (beta < 0.0f ||  1.0f < beta)
			return false;

		float gamma = (a * ( h * k - g * l) + d * ( g * i - e * k ) + c * (e * l - h * i) ) * invDet;
		if (gamma < 0.0f || 1.0f < gamma)
			return false;
		
		if (beta + gamma > 1.0f)
			return false;
		float t = (a * (f * l - h * j) + b * (g * i - e * k) + c * (e * j - f * i)) * invDet;

		if (t < eps)
			return false;

		_tMin = t;
		_sr.normal = n;

		return true;
	}

	bool Triangle::ShadowHit(const Ray& _ray, float& _t) const
	{
		if (!m_Shadow)
			return false;

		float a = p0.x - p1.x;
		float e = p0.y - p1.y;
		float i = p0.z - p1.z;

		float b = p0.y - p2.y;
		float f = p0.y - p2.y;
		float j = p0.y - p2.y;

		float c = _ray.d.x;
		float g = _ray.d.y;
		float k = _ray.d.z;

		float d = p0.x - _ray.o.x;
		float h = p0.y - _ray.o.y;
		float l = p0.z - _ray.o.z;

		float invDet = 1.0f / (a * (f * k - g * j) + b * (g * i - e * k) + c * (e * j - f * i));

		float beta = (d * (f * k - g * j) + b * (g * l - h * k) + c * (h * j - f * l)) * invDet;
		if (0.0f < beta || 1.0f < beta)
			return false;

		float gamma = (a * (h * k - h * j) + b * (g * i - e * k) + c * (e * l - h * i)) * invDet;
		if (0.0f < gamma || 1.0f < gamma)
			return false;

		if (beta + gamma > 1.0f)
			return false;
		float t = (a * (f * l - h * j) + b * (g * i - e * k) + c * (e * j - f * i)) * invDet;

		if (t < eps)
			return false;

		_t = t;

		return true;
	}

	Point3 Triangle::Sample() const
	{
		Point2 p = m_Sampler->SampleUnitSquare();
		float etha = sqrt(p.x);
		float beta = 1.0f - etha;
		float gamma = p.y * etha;
		//http://www.pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations.html#SamplingaTriangle

		float alpha = 1.0f - beta - gamma;
		return alpha * p0 + beta * p1 + gamma * p2;
	}

	float Triangle::pdf(const HitRecord&) const
	{
		return invArea;
	}

	Vector Triangle::Normal(const Point3&) const
	{
		return n;
	}
}