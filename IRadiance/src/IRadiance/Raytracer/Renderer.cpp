#include "pch.h"
#include "Renderer.h"

#include "IRadiance/Raytracer/Maths/Point2.h"
#include "IRadiance/Raytracer/Maths/Point3.h"

#include "IRadiance/Raytracer/Tracers/SingleObject.h"
#include "IRadiance/Raytracer/Tracers/MultiObject.h"

#include "IRadiance/Raytracer/Geometry/Sphere.h"
#include "IRadiance/Raytracer/Geometry/Plane.h"
#include "IRadiance/Raytracer/Geometry/Rectangle.h"

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
#include "IRadiance/Raytracer/Lights/AreaLight.h"

#include "IRadiance/Raytracer/Tracers/RayCast.h"
#include "IRadiance/Raytracer/Tracers/AreaLighting.h"

#include "IRadiance/Raytracer/Materials/Matte.h"
#include "IRadiance/Raytracer/Materials/Phong.h"
#include "IRadiance/Raytracer/Materials/Emissive.h"

#include "IRadiance/Raytracer/ToneMapper/Clamper.h"
#include "IRadiance/Raytracer/ToneMapper/Overflower.h"
#include "Geometry/Box.h"
#include "Samplers/PureRandomSampler.h"


namespace IRadiance
{
	Renderer::~Renderer()
	{
		delete m_Display;
		delete m_CollisionHandler;
		delete m_Scene;
		delete m_Camera;
		delete m_Tracer;
	}

	Display* Renderer::GetDisplay() const
	{
		return m_Display;
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

	ToneMapper* Renderer::GetToneMapper() const
	{
		return m_ToneMapper;
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

		m_Display = new Display;
		m_Display->SetGamma(2.2f);

		m_CollisionHandler = new CollisionHandler(this);
		m_Scene = new SceneGraph;
		
		m_ToneMapper = new Clamper;

		//int num_samples = 1;   		// for Figure 18.4(a)
		int num_samples = 100;   	// for Figure 18.4(b) & (c)

		Sampler* sampler_ptr = new MultiJitteredSampler(num_samples);

		m_ViewingPlane.m_HorRes = m_Buffer->GetWidth();
		m_ViewingPlane.m_VertRes = m_Buffer->GetHeight();
		m_ViewingPlane.SetSampler(sampler_ptr);

		m_BackColor = RGBSpectrum(0.5);

		m_Tracer = new AreaLighting(this);

		CameraDesc desc;
		desc.eye = { -20, 10, 25 };
		desc.lookAt = { 0, 2, 0 };
		m_Camera = new PinholeCamera(desc, 1.0f, 1080);

		Emissive* emissive_ptr = new Emissive;
		emissive_ptr->SetLs(40.0f);
		emissive_ptr->SetCe(WHITE);


		// define a rectangle for the rectangular light

		float width = 4.0f;				// for Figure 18.4(a) & (b)
		float height = 4.0f;
		//	float width = 2.0;				// for Figure 18.4(c)
		//	float height = 2.0;
		Point3 center(0.0f, 7.0f, -7.0f);	// center of each area light (rectangular, disk, and spherical)
		Point3 p0(-0.5f * width, center.y - 0.5f * height, center.z);
		Vector a(width, 0.0f, 0.0f);
		Vector b(0.0f, height, 0.0f);

		Rectangle* rectangle_ptr = new Rectangle(p0, a, b);
		rectangle_ptr->SetMaterial(emissive_ptr);
		rectangle_ptr->SetSampler(sampler_ptr);
		rectangle_ptr->SetShadow(false);
		m_Scene->AddObject(rectangle_ptr);


		AreaLight* area_light_ptr = new AreaLight;
		area_light_ptr->SetObject(rectangle_ptr);
		area_light_ptr->SetShadow(true);
		m_Scene->AddLight(area_light_ptr);


		// Four axis aligned boxes

		float box_width = 1.0f; 		// x dimension
		float box_depth = 1.0f; 		// z dimension
		float box_height = 4.5f; 		// y dimension
		float gap = 3.0f;

		Matte* matte_ptr1 = new Matte;
		matte_ptr1->SetKa(0.25f);
		matte_ptr1->SetKd(0.75f);
		matte_ptr1->SetCd({ 0.4f, 0.7f, 0.4f });     // green

		Box* box_ptr0 = new Box(Point3(-1.5f * gap - 2.0f * box_width, 0.0f, -0.5f * box_depth),
			Point3(-1.5f * gap - box_width, box_height, 0.5f * box_depth));
		box_ptr0->SetMaterial(matte_ptr1);
		m_Scene->AddObject(box_ptr0);

		Box* box_ptr1 = new Box(Point3(-0.5f * gap - box_width, 0.0f, -0.5f * box_depth),
			Point3(-0.5f * gap, box_height, 0.5f * box_depth));
		box_ptr1->SetMaterial(matte_ptr1);
		m_Scene->AddObject(box_ptr1);

		Box* box_ptr2 = new Box(Point3(0.5f * gap, 0.0f, -0.5f * box_depth),
			Point3(0.5f * gap + box_width, box_height, 0.5f * box_depth));
		box_ptr2->SetMaterial(matte_ptr1);
		m_Scene->AddObject(box_ptr2);

		Box* box_ptr3 = new Box(Point3(1.5f * gap + box_width, 0.0f, -0.5f * box_depth),
			Point3(1.5f * gap + 2.0f * box_width, box_height, 0.5f * box_depth));
		box_ptr3->SetMaterial(matte_ptr1);
		m_Scene->AddObject(box_ptr3);


		// ground plane

		Matte* matte_ptr2 = new Matte;
		matte_ptr2->SetKa(0.1f);
		matte_ptr2->SetKd(0.90f);
		matte_ptr2->SetCd(WHITE);

		Plane* plane_ptr = new Plane(Point3(0.0f), Vector(0, 1, 0));
		plane_ptr->SetMaterial(matte_ptr2);
		m_Scene->AddObject(plane_ptr);

		//int nbSamples = 4;
		//Sampler* sampler = new MultiJitteredSampler(nbSamples);
		//m_ViewingPlane.m_HorRes = m_Buffer->GetWidth();
		//m_ViewingPlane.m_VertRes = m_Buffer->GetHeight();
		//m_ViewingPlane.m_PixelSize = 1.0f;
		//m_ViewingPlane.SetSampler(sampler);

		//CameraDesc desc;
		//desc.eye = { 0, 25, 100 };
		//desc.lookAt = { 0, 0, 0 };

		//m_Camera = new PinholeCamera(desc, 1.0f, 6500);
		//m_Camera->ComputeONB();

		//m_BackColor = RED;
		//m_Tracer = new AreaLighting(this);

		//AmbientLight* ambientLight = new AmbientLight;
		//ambientLight->SetLs(0.01f);
		//m_Scene->SetAmbientLight(ambientLight);

		//float width = 2.0f;				// for Figure 18.4(a) & (b)
		//float height = 2.0f;
		////	float width = 2.0;				// for Figure 18.4(c)
		////	float height = 2.0;
		//Point3 center(0.0f, 2.5f, -1.0f);	// center of each area light (rectangular, disk, and spherical)
		//Point3 p0(-0.5f * width, center.y - 0.5f * height, center.z);
		//Vector a(width, 0.0f, 0.0f);
		//Vector b(0.0f, height, 0.0f);

		//Emissive* emissive_ptr = new Emissive;
		//emissive_ptr->SetLs(20.0);
		//emissive_ptr->SetCe(WHITE);

		//Rectangle* rectangle_ptr = new Rectangle(p0, a, b);
		//rectangle_ptr->SetMaterial(emissive_ptr);
		//rectangle_ptr->SetSampler(sampler);
		//rectangle_ptr->SetShadow(false);
		//m_Scene->AddObject(rectangle_ptr);
		//AreaLight* light = new AreaLight;
		//light->SetObject(rectangle_ptr);
		//light->SetShadow(true);
		//m_Scene->AddLight(light);
		//
		//float radius = 1.0f;
		//float gap = 0.2f;	 // gap between spheres

		//Matte* matte_ptr1 = new Matte;
		//matte_ptr1->SetKa(0.0f);
		//matte_ptr1->SetKd(0.75f);
		//matte_ptr1->SetCd({ 1, 0, 0 });		// red
		////matte_ptr1->SetExp(1.0f); 
		//Sphere* sphere_ptr1 = new Sphere({ -3.0f * radius - 1.5f * gap, 0.0f, 0.0f }, radius);
		//sphere_ptr1->SetMaterial(matte_ptr1);
		//m_Scene->AddObject(sphere_ptr1);
		//

		//Matte* matte_ptr2 = new Matte;
		//matte_ptr2->SetKa(0.0f);
		//matte_ptr2->SetKd(0.75f);
		//matte_ptr2->SetCd({ 1, 0.5f, 0 });		// orange
		////matte_ptr2->SetExp(5.0f);

		//Sphere* sphere_ptr2 = new Sphere({ -radius - 0.5f * gap, 0.0, 0.0 }, radius);
		//sphere_ptr2->SetMaterial(matte_ptr2);
		//m_Scene->AddObject(sphere_ptr2);


		//Matte* matte_ptr3 = new Matte;
		//matte_ptr3->SetKa(0.0);
		//matte_ptr3->SetKd(0.75f);
		//matte_ptr3->SetCd({ 1, 1, 0 });		// yellow
		////matte_ptr3->SetExp(25.0f);

		//Sphere* sphere_ptr3 = new Sphere({ radius + 0.5f * gap, 0.0, 0.0 }, radius);
		//sphere_ptr3->SetMaterial(matte_ptr3);
		//m_Scene->AddObject(sphere_ptr3);


		//Matte* matte_ptr4 = new Matte;
		//matte_ptr4->SetKa(0.0f);
		//matte_ptr4->SetKd(0.75f);
		//matte_ptr4->SetCd({0, 1, 0});		// green
		////matte_ptr4->SetExp(50.0f);

		//Sphere* sphere_ptr4 = new Sphere({3.0f * radius + 1.5f * gap, 0.0, 0.0}, radius);
		//sphere_ptr4->SetMaterial(matte_ptr4);
		//m_Scene->AddObject(sphere_ptr4);

		//// ground plane

		//Matte* matte_ptr5 = new Matte;
		//matte_ptr5->SetKa(0.25f);
		//matte_ptr5->SetKd(0.5f);
		//matte_ptr5->SetCd(1.0f);
		////matte_ptr5->SetKs(1.5f);
		////matte_ptr5->SetExp(5.0f);
		//Plane* plane_ptr = new Plane({0, -1, 0}, Vector(0, 1, 0));
		//plane_ptr->SetMaterial(matte_ptr5);
		//m_Scene->AddObject(plane_ptr);

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