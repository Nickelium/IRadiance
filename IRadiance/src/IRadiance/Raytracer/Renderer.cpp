#include "pch.h"
#include "Renderer.h"

#include "IRadiance/Raytracer/Maths/Point2.h"
#include "IRadiance/Raytracer/Maths/Point3.h"

#include "IRadiance/Raytracer/Tracers/SingleObject.h"
#include "IRadiance/Raytracer/Tracers/MultiObject.h"

#include "IRadiance/Raytracer/Geometry/Sphere.h"
#include "IRadiance/Raytracer/Geometry/Plane.h"

#include "IRadiance/Framework/Renderer/ImageBuffer.h"

#include "Samplers/RegularSampler.h"
#include "Samplers/RandomSampler.h"
#include "Samplers/JitteredSampler.h"
#include "Samplers/NRookSampler.h"
#include "Samplers/MultiJitteredSampler.h"

#include "IRadiance/Raytracer/Maths/Utilities.h"

#include "IRadiance/Raytracer/Cameras/Camera.h"
#include "IRadiance/Raytracer/Cameras/PinholeCamera.h"

#include "IRadiance/Raytracer/Lights/AmbientLight.h"

namespace IRadiance
{
	Renderer::~Renderer()
	{
		delete m_Camera;
		delete m_Tracer;
		for (Object* object : m_Objects)
			delete object;
		delete m_AmbientLight;
		for (Light* light : m_Lights)
			delete light;
	}

	const std::vector<Object*>& Renderer::GetObjects() const
	{
		return m_Objects;
	}

	Camera* Renderer::GetCamera() const
	{
		return m_Camera;
	}

	const ViewPlane& Renderer::GetViewPlane() const
	{
		return m_ViewingPlane;
	}

	RGBSpectrum Renderer::GetBackColor() const
	{
		return m_BackColor;
	}

	ImageBuffer* Renderer::GetImageBuffer() const
	{
		return m_Buffer;
	}

	Tracer* Renderer::GetTracer() const
	{
		return m_Tracer;
	}

	CoVariables& Renderer::GetCoVariables()
	{
		return m_CoVars;
	}

	Timer& Renderer::GetTimer()
	{
		return m_Timer;
	}

	void Renderer::Build(ImageBuffer* _buffer)
	{
		m_Buffer = _buffer;

		m_ViewingPlane.m_HorRes = m_Buffer->GetWidth();
		m_ViewingPlane.m_VertRes = m_Buffer->GetHeight();
		m_ViewingPlane.m_PixelSize = 1.0f;
		m_ViewingPlane.SetGamma(1.0f);
		int nbSamples = 4;
		m_ViewingPlane.SetSampler(new MultiJitteredSampler(nbSamples));
			
		CameraDesc desc;
		desc.eye = {0, 2, 0};
		desc.lookAt = {0, 0, 0};

		m_Camera = new PinholeCamera(desc, 1, 73);
		m_Camera->ComputeONB();

		m_BackColor = BLACK;
		m_Tracer = new MultiObject(this);

		float d = 2.0f; 		// sphere center spacing 
		float r = 0.75f; 	// sphere radius
		float xc, yc; 		// sphere center coordinates
		int num_rows = 5;
		int num_columns = 5;

		for (int k = 0; k < num_columns; k++) 		// up
			for (int j = 0; j < num_rows; j++) {	// across
				xc = d * (j - (num_columns - 1) / 2.0f);
				yc = d * (k - (num_rows - 1) / 2.0f);
				Sphere* sphere_ptr = new Sphere({xc, 0, yc}, r);
				AddObject(sphere_ptr);
			}

		m_AmbientLight = new AmbientLight;
		/*AddObject(new Sphere({0.0f, 0.0f, -100.0f}, 100.0f));
		AddObject(new Sphere({ +75, 0, -100.0f}, 75));
		AddObject(new Sphere({ -75, 0, -100.0f}, 75));*/

		//Sphere* sphere_ptr = new Sphere;
		//sphere_ptr->SetCenter({ 0, -25, 0 });
		//sphere_ptr->SetRadius(80);
		//sphere_ptr->SetColor({ 1, 0, 0 }); // red
		//AddObject(sphere_ptr);
		//// use constructor to set sphere center and radius
		//sphere_ptr = new Sphere(Point3(0, 30, 0), 60);
		//sphere_ptr->SetColor({1, 1, 0}); // yellow
		//AddObject(sphere_ptr);
		//Plane* plane_ptr = new Plane(Point3(0, 0, 0), Normal(0, 1, 1));
		//plane_ptr->SetColor({ 168/255.0f, 212 / 255.0f, 211.0f / 255.0f }); // dark green
		//AddObject(plane_ptr);

		//AddObject(new Sphere({ 0, -1000, 0 }, 1000));
		//int gridSize = 5;
		//for (int a = -gridSize; a < gridSize; a++) 
		//{
		//	for (int b = -gridSize; b < gridSize; b++) 
		//	{
		//		float choose_mat = RandSNorm();
		//		Point3 center(a + 0.9f * RandSNorm(), 0.2f, b + 0.9f * RandSNorm());
		//		if (Length(center - Point3(4, 0.2f, 0)) > 0.9f) 
		//		{
		//			if (choose_mat < 0.8) 
		//			{  // diffuse
		//				AddObject(new Sphere(center, 0.2f));
		//			}
		//			else if (choose_mat < 0.95) 
		//			{ // metal
		//				AddObject(new Sphere(center, 0.2f));
		//			}
		//			else
		//			{  // glass
		//				AddObject(new Sphere(center, 0.2f));
		//			}
		//		}
		//	}
		//}

		//AddObject(new Sphere({ 0, 1, 0 }, 1));
		//AddObject(new Sphere({-4, 1, 0 }, 1));
		//AddObject(new Sphere({ 4, 1, 0 }, 1));

	}

	void Renderer::PreRender()
	{
		m_CoVars.row = 0;
		m_CoVars.col = 0;
		m_Timer.Start();
	}

	bool Renderer::Render()
	{
		return m_Camera->Render(this);
	}

	void Renderer::AddObject(Object* _object)
	{
		m_Objects.push_back(_object);
	}

	void Renderer::AddLight(Light* _light)
	{
		m_Lights.push_back(_light);
	}

}