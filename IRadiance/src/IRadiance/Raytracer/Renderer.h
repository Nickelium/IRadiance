#pragma once

#include "ViewPlane.h"
#include "IRadiance/Raytracer/Geometry/Object.h"
#include "RGBSpectrum.h"
#include "IRadiance/Raytracer/Collision/CollisionHandler.h"
#include "IRadiance/Raytracer/SceneGraph.h"


namespace IRadiance
{
	class Tracer;
	class Camera;
	class ImageBuffer;
	class Light;
	/**
	 * Coroutine variables for resuming rendering
	 */
	struct CoVariables
	{
		int row;
		int col;
	};

	class Renderer
	{
	public:
		~Renderer();

		ViewPlane* GetViewPlane();
		RGBSpectrum GetBackColor() const;
		Camera* GetCamera() const;
		Tracer* GetTracer() const;
		SceneGraph* GetScene() const;
		ImageBuffer* GetImageBuffer() const;
		CollisionHandler* GetCollisionHandler() const;

		CoVariables& GetCoVariables();
		Timer& GetTimer();

		void Build(ImageBuffer* _buffer);

		void PreRender();
		bool Render();
	private:
		ViewPlane m_ViewingPlane;
		Camera* m_Camera;
		Tracer* m_Tracer;
		RGBSpectrum m_BackColor;
		SceneGraph* m_Scene;

		//CollisionHandler
		CollisionHandler* m_CollisionHandler;

		ImageBuffer* m_Buffer;

		CoVariables m_CoVars;
		Timer m_Timer;
	};
}
