#pragma once

#include "ViewPlane.h"
#include "IRadiance/Raytracer/Geometry/Object.h"
#include "RGBSpectrum.h"

namespace IRadiance
{
	class Tracer;
	class ImageBuffer;

	class Renderer
	{
	public:
		~Renderer();

		inline const std::vector<Object*>& GetObjects() const
		{
			return m_Objects;
		}

		inline RGBSpectrum GetBackColor() const
		{
			return m_BackColor;
		}

		void Build(ImageBuffer* _buffer);

		void PreRender();
		bool Render();
	private:

		inline void AddObject(Object* _object)
		{
			m_Objects.push_back(_object);
		}

		ViewPlane m_ViewingPlane;
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
		Timer m_Timer;
	};
}
