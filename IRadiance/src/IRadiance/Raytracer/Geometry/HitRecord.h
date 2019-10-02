#pragma once

#include "IRadiance/Raytracer/Maths/Point3.h"
#include "IRadiance/Raytracer/Maths/Normal.h"

#include "IRadiance/Raytracer/RGBSpectrum.h"

namespace IRadiance
{
	class Renderer;
	class Material;
	struct HitRecord
	{
		bool hasHit = false;
		Material* material;
		Point3 hitPoint;
		Point3 localHitPoint; //textures TODO
		Vector normal;
		Ray ray; //Specular lights
		int depth;
		Vector direction; //Area Lights
		float t;
		Renderer* renderer;
		HitRecord(Renderer* _renderer)
			: hasHit(false), material(nullptr),
			hitPoint(), localHitPoint(), normal(),
			ray(), depth(0), direction(), t(Constants::MaxValue),
			renderer(_renderer){}

	};
}