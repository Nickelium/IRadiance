#pragma once

#include "ViewPlane.h"
#include "IRadiance/Raytracer/Geometry/Object.h"
#include "IRadiance/Raytracer/Geometry/Sphere.h"
#include "RGBSpectrum.h"

namespace IRadiance
{
	class Tracer;
	class ImageBuffer;

	class Renderer
	{
	public:
		~Renderer();

		inline void AddObject(Object* _object)
		{
			m_Objects.push_back(_object);
		}
		inline const std::vector<Object*>& GetObjects() const
		{
			return m_Objects;
		}

		void Build(ImageBuffer* _buffer);

		void PreRender();
		void Render();
		Sphere m_Sphere;
	private:
		ViewPlane m_ViewingPlane;

		//Scene
		std::vector<Object*> m_Objects;

		Tracer* m_Tracer;

		RGBSpectrum m_BackColor;
		ImageBuffer* m_Buffer;

		struct CoVariables
		{
			int row;
			int col;
		};
		CoVariables coVars;
	};
}
