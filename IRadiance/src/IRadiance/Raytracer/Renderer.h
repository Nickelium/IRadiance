#pragma once

#include "ViewPlane.h"
#include "IRadiance/Raytracer/Geometry/Object.h"
#include "RGBSpectrum.h"

namespace IRadiance
{
	class Tracer;
	class Camera;
	class ImageBuffer;

	struct CoVariables
	{
		int row;
		int col;
	};

	class Renderer
	{
	public:
		~Renderer();

		RGBSpectrum GetBackColor() const;

		const std::vector<Object*>& GetObjects() const;
		Camera* GetCamera() const;
		const ViewPlane& GetViewPlane() const;
		ImageBuffer* GetImageBuffer() const;
		Tracer* GetTracer() const;

		CoVariables& GetCoVariables();
		Timer& GetTimer();

		void Build(ImageBuffer* _buffer);

		void PreRender();
		bool Render();
	private:

		void AddObject(Object* _object);

		Camera* m_Camera;
		ViewPlane m_ViewingPlane;
		std::vector<Object*> m_Objects;

		Tracer* m_Tracer;

		RGBSpectrum m_BackColor;
		ImageBuffer* m_Buffer;

		CoVariables m_CoVars;
		Timer m_Timer;
	};
}
