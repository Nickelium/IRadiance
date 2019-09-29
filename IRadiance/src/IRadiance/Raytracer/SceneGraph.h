#pragma once

#include "IRadiance/Raytracer/Geometry/Object.h"
#include "IRadiance/Raytracer/Lights/Light.h"

namespace IRadiance
{
	class SceneGraph
	{
	public:
		SceneGraph();
		~SceneGraph();

		void AddObject(const Object* _object);
		void AddLight(const Light* _light);
		void SetAmbientLight(const Light* _ambientLight);

		const std::vector<const Object*>& GetObjects() const;
		const std::vector<const Light*>& GetLights() const;
		const Light* GetAmbientLight() const;
	private:
		std::vector<const Object*> m_Objects;
		std::vector<const Light*> m_Lights;

		const Light* m_AmbientLight;
	};
}
		