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
#include "IRadiance/Raytracer/Lights/PointLight.h"
#include "IRadiance/Raytracer/Lights/DirectionalLight.h"
#include "IRadiance/Raytracer/Tracers/RayCast.h"
#include "IRadiance/Raytracer/Materials/Matte.h"

namespace IRadiance
{
	Renderer::~Renderer()
	{
		delete m_CollisionHandler;
		delete m_Scene;
		delete m_Camera;
		delete m_Tracer;
	}

	SceneGraph* Renderer::GetScene() const
	{
		return m_Scene;
	}

	Camera* Renderer::GetCamera() const
	{
		return m_Camera;
	}

	ViewPlane* Renderer::GetViewPlane() 
	{
		return &m_ViewingPlane;
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

	CollisionHandler* Renderer::GetCollisionHandler() const
	{
		return m_CollisionHandler;
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

		m_CollisionHandler = new CollisionHandler(this);
		m_Scene = new SceneGraph;

		m_ViewingPlane.m_HorRes = m_Buffer->GetWidth();
		m_ViewingPlane.m_VertRes = m_Buffer->GetHeight();
		m_ViewingPlane.m_PixelSize = 1.0f;
		m_ViewingPlane.SetGamma(1.0f);
		int nbSamples = 16;
		m_ViewingPlane.SetSampler(new MultiJitteredSampler(nbSamples));
			
		CameraDesc desc;
		desc.eye = {0, 0, 500};
		desc.lookAt = {-5, 0, 0};

		m_Camera = new PinholeCamera(desc, 1, 850);
		m_Camera->ComputeONB();

		m_BackColor = RED;
		m_Tracer = new RayCast(this);

		//float d = 2.0f; 		// sphere center spacing 
		//float r = 0.75f; 	// sphere radius
		//float xc, yc; 		// sphere center coordinates
		//int num_rows = 5;
		//int num_columns = 5;

		//for (int k = 0; k < num_columns; k++) 		// up
		//	for (int j = 0; j < num_rows; j++) {	// across
		//		xc = d * (j - (num_columns - 1) / 2.0f);
		//		yc = d * (k - (num_rows - 1) / 2.0f);
		//		Sphere* sphere_ptr = new Sphere({xc, 0, yc}, r);
		//		m_Scene->AddObject(sphere_ptr);
		//	}
		
		m_Scene->SetAmbientLight(new AmbientLight);
		PointLight* pointLight = new PointLight;
		pointLight->SetPosition({ 100, 50, 150});
		pointLight->SetLs(3);
		m_Scene->AddLight(pointLight);

		Matte* matte1 = new Matte;
		matte1->SetKa(0.25f);
		matte1->SetKd(0.65f);
		matte1->SetCd({ 1, 1, 0 });	  				
		Sphere* sphere1 = new Sphere({ 0, 0, 0 }, 27);
		sphere1->SetMaterial(matte1);
		m_Scene->AddObject(sphere1);

		//Matte* matte2 = new Matte;
		//matte2->SetKa(0.15f);
		//matte2->SetKd(0.85f);
		//matte2->SetCd({ 0.71f, 0.40f, 0.16f });
		//Sphere* sphere2 = new Sphere({ -25, 10, -35 }, 27);
		//sphere2->SetMaterial(matte2);
		//m_Scene->AddObject(sphere2);

		//Matte* matte3 = new Matte;
		//matte3->SetKa(0.15f);
		//matte3->SetKd(0.5f);
		//matte3->SetCd({ 0.f, 0.4f, 0.2f });			
		//Plane* plane = new Plane({ 0, 0, -50 }, Normal(0, 0, 1));
		//plane->SetMaterial(matte3);
		//m_Scene->AddObject(plane);


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

}