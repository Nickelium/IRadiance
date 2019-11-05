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

		void SetTracer(Tracer* _tracer);

		Display* GetDisplay() const;
		ViewPlane* GetViewPlane();
		ToneMapper* GetToneMapper() const;
		RGBSpectrum GetBackColor() const;
		Camera* GetCamera() const;
		Tracer* GetTracer() const;
		SceneGraph* GetScene() const;
		ImageBuffer* GetImageBuffer() const;
		CollisionHandler* GetCollisionHandler() const;

		void SetNbSamples(int _nbSamples);
		int GetNbSamples() const;

		bool IsRunning() const;
		void Stop();
		void Run();

		int MaxDepth() const;

		void Build(ImageBuffer* _buffer);

		bool Render();

		using BuildFunction = std::function<void(void)>;
		using BuildTFunctions = std::vector<std::pair<std::string, BuildFunction>>;

		inline const BuildTFunctions& GetBuildFunctions() const { return m_BuildFunctions; }
		void LoadScene(const BuildFunction& f);
	private:
		BuildTFunctions m_BuildFunctions;

		void BuildCornellBoxData();
		void BuildCornellBox();
		void BuildCaustics();
		void BuildReflection();
		void BuildRefraction();

		Display* m_Display;
		ViewPlane m_ViewingPlane;
		ToneMapper* m_ToneMapper;
		Camera* m_Camera;
		Tracer* m_Tracer;
		RGBSpectrum m_BackColor;
		SceneGraph* m_Scene;

		//TODO MAKE SAMPLER
		// THEN SET BUILD FUNCTION TO REFER TO THIS
		Sampler* m_Sampler;


		//CollisionHandler
		CollisionHandler* m_CollisionHandler;

		ImageBuffer* m_Buffer;

		int m_MaxDepth;

		std::atomic<bool> m_IsRunning;
	};
}
