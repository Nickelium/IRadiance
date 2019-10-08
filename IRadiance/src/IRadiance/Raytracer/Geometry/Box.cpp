#include "pch.h"
#include "Box.h"

namespace IRadiance
{
	const float Box::eps = 0.001f;

	Box::Box(const Point3& _minPoint, const Point3& _maxPoint)
		: minPoint(_minPoint), maxPoint(_maxPoint)
	{
	}

	bool Box::Hit(const Ray& _ray, float& _tMin, HitRecord& _sr) const
	{
		float x0 = minPoint.x;
		float y0 = minPoint.y;
		float z0 = minPoint.z;
		float x1 = maxPoint.x;
		float y1 = maxPoint.y;
		float z1 = maxPoint.z;

		// this is the same as Listing 19.1 down to the statement float t0, t1;
		float ox =_ray.o.x; float oy =_ray.o.y; float oz =_ray.o.z;
		float dx =_ray.d.x; float dy =_ray.d.y; float dz =_ray.d.z;

		float tx_min, ty_min, tz_min;
		float tx_max, ty_max, tz_max;


		float a = 1.0f / dx;
		if (a >= 0) {
			tx_min = (x0 - ox) * a;
			tx_max = (x1 - ox) * a;
		}
		else {
			tx_min = (x1 - ox) * a;
			tx_max = (x0 - ox) * a;
		}

		float b = 1.0f / dy;
		if (b >= 0) {
			ty_min = (y0 - oy) * b;
			ty_max = (y1 - oy) * b;
		}
		else {
			ty_min = (y1 - oy) * b;
			ty_max = (y0 - oy) * b;
		}

		float c = 1.0f / dz;
		if (c >= 0) {
			tz_min = (z0 - oz) * c;
			tz_max = (z1 - oz) * c;
		}
		else {
			tz_min = (z1 - oz) * c;
			tz_max = (z0 - oz) * c;
		}

		float t0, t1;

		// find largest entering t value

		if (tx_min > ty_min)
			t0 = tx_min;
		else
			t0 = ty_min;

		if (tz_min > t0)
			t0 = tz_min;

		// find smallest exiting t value

		if (tx_max < ty_max)
			t1 = tx_max;
		else
			t1 = ty_max;

		if (tz_max < t1)
			t1 = tz_max;

		int face_in, face_out;

		// find largest entering t value

		if (tx_min > ty_min) {
			t0 = tx_min;
			face_in = (a >= 0.0) ? 0 : 3;
		}
		else {
			t0 = ty_min;
			face_in = (b >= 0.0) ? 1 : 4;
		}

		if (tz_min > t0) {
			t0 = tz_min;
			face_in = (c >= 0.0) ? 2 : 5;
		}

		// find smallest exiting t value

		if (tx_max < ty_max) {
			t1 = tx_max;
			face_out = (a >= 0.0) ? 3 : 0;
		}
		else {
			t1 = ty_max;
			face_out = (b >= 0.0) ? 4 : 1;
		}

		if (tz_max < t1) {
			t1 = tz_max;
			face_out = (c >= 0.0) ? 5 : 2;
		}

		if (t0 < t1 && t1 > eps) {  // condition for a hit
			if (t0 > eps) {
				_tMin = t0;  			//_ray hits outside surface
				_sr.normal = Normal(face_in);
			}
			else {
				_tMin = t1;				//_ray hits inside surface
				_sr.normal = Normal(face_out);
			}

			_sr.hitPoint =_ray.o + _tMin *_ray.d;
			return (true);
		}
		else
			return (false);
	}

	//TODO box problem hide
	bool Box::ShadowHit(const Ray& _ray, float& _t) const
	{
		float x0 = minPoint.x;
		float y0 = minPoint.y;
		float z0 = minPoint.z;
		float x1 = maxPoint.x;
		float y1 = maxPoint.y;
		float z1 = maxPoint.z;

		// this is the same as Listing 19.1 down to the statement float t0, t1;
		float ox = _ray.o.x; float oy = _ray.o.y; float oz = _ray.o.z;
		float dx = _ray.d.x; float dy = _ray.d.y; float dz = _ray.d.z;

		float tx_min, ty_min, tz_min;
		float tx_max, ty_max, tz_max;


		float a = 1.0f / dx;
		if (a >= 0) {
			tx_min = (x0 - ox) * a;
			tx_max = (x1 - ox) * a;
		}
		else {
			tx_min = (x1 - ox) * a;
			tx_max = (x0 - ox) * a;
		}

		float b = 1.0f / dy;
		if (b >= 0) {
			ty_min = (y0 - oy) * b;
			ty_max = (y1 - oy) * b;
		}
		else {
			ty_min = (y1 - oy) * b;
			ty_max = (y0 - oy) * b;
		}

		float c = 1.0f / dz;
		if (c >= 0) {
			tz_min = (z0 - oz) * c;
			tz_max = (z1 - oz) * c;
		}
		else {
			tz_min = (z1 - oz) * c;
			tz_max = (z0 - oz) * c;
		}

		float t0, t1;

		// find largest entering t value

		if (tx_min > ty_min)
			t0 = tx_min;
		else
			t0 = ty_min;

		if (tz_min > t0)
			t0 = tz_min;

		// find smallest exiting t value

		if (tx_max < ty_max)
			t1 = tx_max;
		else
			t1 = ty_max;

		if (tz_max < t1)
			t1 = tz_max;

		int face_in, face_out;

		// find largest entering t value

		if (tx_min > ty_min) {
			t0 = tx_min;
			face_in = (a >= 0.0) ? 0 : 3;
		}
		else {
			t0 = ty_min;
			face_in = (b >= 0.0) ? 1 : 4;
		}

		if (tz_min > t0) {
			t0 = tz_min;
			face_in = (c >= 0.0) ? 2 : 5;
		}

		// find smallest exiting t value

		if (tx_max < ty_max) {
			t1 = tx_max;
			face_out = (a >= 0.0) ? 3 : 0;
		}
		else {
			t1 = ty_max;
			face_out = (b >= 0.0) ? 4 : 1;
		}

		if (tz_max < t1) {
			t1 = tz_max;
			face_out = (c >= 0.0) ? 5 : 2;
		}

		if (t0 < t1 && t1 > eps) {  // condition for a hit
			if (t0 > eps) {
				_t = t0;  			//_ray hits outside surface
			}
			else {
				_t = t1;				//_ray hits inside surface
			}

			return (true);
		}
		else
			return (false);
	}

	Vector Box::Normal(const int _faceHit) const
	{
		switch (_faceHit)
		{
			case 0:	return (Vector(-1, 0, 0));	// -x face
			case 1:	return (Vector(0, -1, 0));	// -y face
			case 2:	return (Vector(0, 0, -1));	// -z face
			case 3:	return (Vector(1, 0, 0));	// +x face
			case 4:	return (Vector(0, 1, 0));	// +y face
			case 5:	return (Vector(0, 0, 1));	// +z face
		}
		return {};
	}

	}