#pragma once

#include "ViewPlane.h"
#include "IRadiance/Raytracer/Geometry/Object.h"
#include "RGBSpectrum.h"
#include "IRadiance/Raytracer/Collision/CollisionHandler.h"
#include "IRadiance/Raytracer/SceneGraph.h"
#include "IRadiance/Raytracer/ToneMapper/ToneMapper.h"
#include "IRadiance/Raytracer/Display.h"

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

		Display* GetDisplay() const;
		ViewPlane* GetViewPlane();
		ToneMapper* GetToneMapper() const;
		RGBSpectrum GetBackColor() const;
		Camera* GetCamera() const;
		Tracer* GetTracer() const;
		SceneGraph* GetScene() const;
		ImageBuffer* GetImageBuffer() const;
		CollisionHandler* GetCollisionHandler() const;

		CoVariables& GetCoVariables();
		Timer& GetTimer();

		int MaxDepth() const;

		void Build(ImageBuffer* _buffer);

		void PreRender();
		bool Render();
	private:
		void BuildObjects();
		Display* m_Display;
		ViewPlane m_ViewingPlane;
		ToneMapper* m_ToneMapper;
		Camera* m_Camera;
		Tracer* m_Tracer;
		RGBSpectrum m_BackColor;
		SceneGraph* m_Scene;

		//CollisionHandler
		CollisionHandler* m_CollisionHandler;

		ImageBuffer* m_Buffer;

		CoVariables m_CoVars;
		Timer m_Timer;

		int m_MaxDepth;
	};
}
