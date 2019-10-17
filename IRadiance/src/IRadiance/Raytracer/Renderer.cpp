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
#include "Lights/EnvironmentLight.h"
#include "Tracers/Whitted.h"
#include "Materials/Reflective.h"
#include "Tracers/PathTracer.h"
#include "Tracers/HybridPathTracer.h"


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

	void Renderer::SetNbSamples(int _nbSamples)
	{
		m_ViewingPlane.SetSampler(new MultiJitteredSampler(_nbSamples));
	}

	int Renderer::GetNbSamples() const
	{
		return m_ViewingPlane.m_NumSamples;
	}

	bool Renderer::IsRunning() const
	{
		return m_IsRunning;
	}

	void Renderer::Stop()
	{
		m_IsRunning = false;
	}

	void Renderer::Run()
	{
		m_IsRunning = true;
	}

	int Renderer::MaxDepth() const
	{
		return m_MaxDepth;
	}

	void Renderer::BuildCornellBox(int _nbSamples)
	{
		Point3 p0;
		Vector a, b;
		Vector normal;

		int num_samples = _nbSamples;

		// box dimensions

		float width = 55.28f;   	// x direction
		float height = 54.88f;  	// y direction
		float depth = 55.92f;	// z direction


		// the ceiling light - doesn't need samples

		Emissive* emissive_ptr = new Emissive;
		emissive_ptr->SetCe({ 1.0f, 0.73f, 0.4f });
		emissive_ptr->SetLs(100);

		p0 = Point3(21.3f, height - 0.001f, 22.7f);
		a = Vector(0.0f, 0.0f, 10.5f);
		b = Vector(13.0f, 0.0f, 0.0f);
		normal = Vector(0.0f, -1.0f, 0.0f);
		Rectangle* light_ptr = new Rectangle(p0, a, b, normal);
		light_ptr->SetMaterial(emissive_ptr);
		m_Scene->AddObject(light_ptr);

		AreaLight* light = new AreaLight;
		light->SetObject(light_ptr);
		light_ptr->SetSampler(new MultiJitteredSampler(num_samples));
		light->SetShadow(true);
		m_Scene->AddLight(light);


		// left wall

		Matte* matte_ptr1 = new Matte;
		matte_ptr1->SetKa(0.0f);
		matte_ptr1->SetKd(0.6f);
		matte_ptr1->SetCd({ 0.57f, 0.025f, 0.025f });	 // red
		matte_ptr1->SetSampler(new MultiJitteredSampler(num_samples));

		p0 = Point3(width, 0.0f, 0.0f);
		a = Vector(0.0f, 0.0f, depth);
		b = Vector(0.0f, height, 0.0f);
		normal = Vector(-1.0f, 0.0f, 0.0f);
		Rectangle* left_wall_ptr = new Rectangle(p0, a, b, normal);
		left_wall_ptr->SetMaterial(matte_ptr1);
		m_Scene->AddObject(left_wall_ptr);


		// right wall

		Matte* matte_ptr2 = new Matte;
		matte_ptr2->SetKa(0.0f);
		matte_ptr2->SetKd(0.6f);
		matte_ptr2->SetCd({0.37f, 0.59f, 0.2f});	 // green   from Photoshop
		matte_ptr2->SetSampler(new MultiJitteredSampler(num_samples));

		p0 = Point3(0.0f, 0.0f, 0.0f);
		a = Vector(0.0f, 0.0f, depth);
		b = Vector(0.0f, height, 0.0f);
		normal = Vector(1.0f, 0.0f, 0.0f);
		Rectangle* right_wall_ptr = new Rectangle(p0, a, b, normal);
		right_wall_ptr->SetMaterial(matte_ptr2);
		m_Scene->AddObject(right_wall_ptr);

		// back wall
		Matte* matte_ptr3 = new Matte;
		matte_ptr3->SetKa(0.0f);
		matte_ptr3->SetKd( 0.6f);
		matte_ptr3->SetCd({ 1.0f, 1.0f, 1.0f });	 // white
		matte_ptr3->SetSampler(new MultiJitteredSampler(num_samples));

		p0 = Point3(0.0f, 0.0f, depth);
		a = Vector(width, 0.0f, 0.0f);
		b = Vector(0.0, height, 0.0f);
		normal = Vector(0.0f, 0.0f, -1.0f);
		Rectangle* back_wall_ptr = new Rectangle(p0, a, b, normal);
		back_wall_ptr->SetMaterial(matte_ptr3);
		m_Scene->AddObject(back_wall_ptr);


		// floor

		p0 = Point3(0.0f, 0.0f, 0.0f);
		a = Vector(0.0f, 0.0f, depth);
		b = Vector(width, 0.0f, 0.0f);
		normal = Vector(0.0f, 1.0f, 0.0f);
		Rectangle* floor_ptr = new Rectangle(p0, a, b, normal);
		floor_ptr->SetMaterial(matte_ptr3);
		m_Scene->AddObject(floor_ptr);


		// ceiling

		p0 = Point3(0.0f, height, 0.0f);
		a = Vector(0.0f, 0.0f, depth);
		b = Vector(width, 0.0f, 0.0f);
		normal = Vector(0.0f, -1.0f, 0.0f);
		Rectangle* ceiling_ptr = new Rectangle(p0, a, b, normal);
		ceiling_ptr->SetMaterial(matte_ptr3);
		m_Scene->AddObject(ceiling_ptr);


		// the two boxes defined as 5 rectangles each

		// short box

		// top

		p0 = Point3(13.0f, 16.5f, 6.5f);
		a = Vector(-4.8f, 0.0f, 16.0f);
		b = Vector(16.0f, 0.0f, 4.9f);
		normal = Vector(0.0f, 1.0f, 0.0f);
		Rectangle* short_top_ptr = new Rectangle(p0, a, b, normal);
		//short_top_ptr->SetMaterial(matte_ptr3);
		short_top_ptr->SetMaterial(matte_ptr3);
		m_Scene->AddObject(short_top_ptr);


		// side 1

		p0 = Point3(13.0f, 0.0f, 6.5f);
		a = Vector(-4.8f, 0.0f, 16.0f);
		b = Vector(0.0f, 16.5f, 0.0f);
		Rectangle* short_side_ptr1 = new Rectangle(p0, a, b);
		short_side_ptr1->SetMaterial(matte_ptr3);
		m_Scene->AddObject(short_side_ptr1);


		// side 2

		p0 = Point3(8.2f, 0.0f, 22.5f);
		a = Vector(15.8f, 0.0f, 4.7f);
		Rectangle* short_side_ptr2 = new Rectangle(p0, a, b);
		short_side_ptr2->SetMaterial(matte_ptr3);
		m_Scene->AddObject(short_side_ptr2);


		// side 3

		p0 = Point3(24.2f, 0.0f, 27.4f);
		a = Vector(4.8f, 0.0f, -16.0f);
		Rectangle* short_side_ptr3 = new Rectangle(p0, a, b);
		short_side_ptr3->SetMaterial(matte_ptr3);
		m_Scene->AddObject(short_side_ptr3);


		// side 4

		p0 = Point3(29.0f, 0.0f, 11.4f);
		a = Vector(-16.0f, 0.0f, -4.9f);
		Rectangle* short_side_ptr4 = new Rectangle(p0, a, b);
		short_side_ptr4->SetMaterial(matte_ptr3);
		m_Scene->AddObject(short_side_ptr4);




		// tall box

		// top

		p0 = Point3(42.3f, 33.0f, 24.7f);
		a = Vector(-15.8f, 0.0f, 4.9f);
		b = Vector(4.9f, 0.0f, 15.9f);
		normal = Vector(0.0f, 1.0f, 0.0f);
		Rectangle* tall_top_ptr = new Rectangle(p0, a, b, normal);
		tall_top_ptr->SetMaterial(matte_ptr3);
		m_Scene->AddObject(tall_top_ptr);


		// side 1

		p0 = Point3(42.3f, 0.0f, 24.7f);
		a = Vector(-15.8f, 0.0f, 4.9f);
		b = Vector(0.0f, 33.0f, 0.0f);
		Rectangle* tall_side_ptr1 = new Rectangle(p0, a, b);
		tall_side_ptr1->SetMaterial(matte_ptr3);
		m_Scene->AddObject(tall_side_ptr1);


		// side 2

		p0 = Point3(26.5f, 0.0f, 29.6f);
		a = Vector(4.9f, 0.0f, 15.9f);
		Rectangle* tall_side_ptr2 = new Rectangle(p0, a, b);
		tall_side_ptr2->SetMaterial(matte_ptr3);
		m_Scene->AddObject(tall_side_ptr2);


		// side 3

		p0 = Point3(31.4f, 0.0f, 45.5f);
		a = Vector(15.8f, 0.0f, -4.9f);
		Rectangle* tall_side_ptr3 = new Rectangle(p0, a, b);
		tall_side_ptr3->SetMaterial(matte_ptr3);
		m_Scene->AddObject(tall_side_ptr3);


		// side 4

		p0 = Point3(47.2f, 0.0f, 40.6f);
		a = Vector(-4.9f, 0.0f, -15.9f);
		Rectangle* tall_side_ptr4 = new Rectangle(p0, a, b);
		tall_side_ptr4->SetMaterial(matte_ptr3);
		m_Scene->AddObject(tall_side_ptr4);
	}

	void Renderer::BuildCaustics(int _nbSamples)
	{
		// emissive sphere
		Emissive* emissive_ptr = new Emissive;
		emissive_ptr->SetCe({ 0.75f, 1, 0.75f });
		emissive_ptr->SetLs(30.0f);

		Sphere* sphere_ptr = new Sphere(Point3(-2, 7, 6), 1);
		sphere_ptr->SetMaterial(emissive_ptr);
		sphere_ptr->SetSampler(new MultiJitteredSampler(_nbSamples));
		m_Scene->AddObject(sphere_ptr);


		// reflective open half cylinder

		Reflective* reflective_ptr = new Reflective;
		reflective_ptr->SetKa(0.0f);
		reflective_ptr->SetKd(0.4f);
		reflective_ptr->SetKs(0.0f);
		reflective_ptr->SetExp(1.0f);
		reflective_ptr->SetKr(0.95f);
		reflective_ptr->SetCr({1.0f, 0.5f, 0.25f});  // orange 

		float y0 = -1.0f;
		float y1 = 3.0f;
		float radius = 3.0f;
		float phi_min = 90.0f;
		float phi_max = 270.0f;

		//ConcavePartCylinder* cylinder_ptr = new ConcavePartCylinder(y0, y1, radius, phi_min, phi_max);
		//cylinder_ptr->SetMaterial(reflective_ptr);
		//m_Scene->AddObject(cylinder_ptr);


		// plane

		Matte* matte_ptr = new Matte;
		matte_ptr->SetKa(0.0f);
		matte_ptr->SetKd(0.75f);
		matte_ptr->SetCd(1);
		matte_ptr->SetSampler(new MultiJitteredSampler(_nbSamples));

		Plane* plane_ptr = new Plane(Point3(0, -1.0f, 0), Vector(0, 1, 0));
		plane_ptr->SetMaterial(matte_ptr);
		m_Scene->AddObject(plane_ptr);
	}

	void Renderer::Build(ImageBuffer* _buffer)
	{
		m_Buffer = _buffer;

		m_Display = new Display;
		m_Display->SetGamma(1.0f);
		//TODO, do actually need to gamma correct because not sampling for texture or so
		//TODO reflection and phong or broken

		m_CollisionHandler = new CollisionHandler(this);
		m_Scene = new SceneGraph;

		m_ToneMapper = new Clamper;

		m_MaxDepth = 1;

		//int num_samples = 100;   		// for Figure 18.4(a)
		int num_samples = 1024;   	// for Figure 18.4(b) & (c)

		//Sampler* sampler_ptr = new MultiJitteredSampler(num_samples);

		m_ViewingPlane.m_HorRes = m_Buffer->GetWidth();
		m_ViewingPlane.m_VertRes = m_Buffer->GetHeight();
		SetNbSamples(num_samples);
		//m_ViewingPlane.SetSampler(sampler_ptr);

		m_BackColor = RGBSpectrum({ 0.0f, 0.0f, 0.0f});

		m_Tracer = new HybridPathTracer(this);

		CameraDesc desc;
		desc.eye = { 27.6f, 27.4f, -80.0f };
		desc.lookAt = { 27.6f, 27.4f, 0.0f };
		m_Camera = new PinholeCamera(desc, 1.0f, 400 /** 2.4f*/);
		m_Camera->ComputeONB();
		BuildCornellBox(num_samples);
		/************************************************************************/
		/* Test Environment Light                                               */
		/************************************************************************/
		//CameraDesc desc;
		//desc.eye = { 100, 45, 100};
		//desc.lookAt = { -10, 40, 0 };
		//m_Camera = new PinholeCamera(desc, 1.0f, 400);
		//m_Camera->ComputeONB();

		//Emissive* emissive_ptr = new Emissive;
		//emissive_ptr->SetLs(5.90f);
		//emissive_ptr->SetCe({ 1.0f, 1.0f, 0.5f });   			// white

		////ConcaveSphere* sphere_ptr = new ConcaveSphere;
		////sphere_ptr->set_radius(1000000.0);
		////sphere_ptr->set_material(emissive_ptr);
		////sphere_ptr->set_shadows(false);
		////add_object(sphere_ptr);


		//EnvironmentLight* environment_light_ptr = new EnvironmentLight;
		//environment_light_ptr->SetMaterial(emissive_ptr);
		//environment_light_ptr->SetSampler(new MultiJitteredSampler(num_samples));
		//environment_light_ptr->SetShadow(true);
		//m_Scene->AddLight(environment_light_ptr);			// for Figure 18.7 (b) & (c)

		//Reflective* reflective_ptr = new Reflective;
		//reflective_ptr->SetKa(0.0f);
		//reflective_ptr->SetKd(0.0f);
		//reflective_ptr->SetCd(BLACK);    	// yellow
		//reflective_ptr->SetKs(0.0f);
		//reflective_ptr->SetExp(1.0f);
		//reflective_ptr->SetKr(0.9f);
		//reflective_ptr->SetCr({ 1.0f, 0.75f, 0.5f });
		//float ka = 0.2f;  // commom ambient reflection coefficient for other objects

		//// large sphere

		//Sphere* sphere_ptr1 = new Sphere(Point3(38, 20, -24), 20);
		//sphere_ptr1->SetMaterial(reflective_ptr);
		//m_Scene->AddObject(sphere_ptr1);


		//// small sphere

		//Matte* matte_ptr2 = new Matte;
		//matte_ptr2->SetKa(ka);
		//matte_ptr2->SetKd(0.5f);
		//matte_ptr2->SetCd({ 0.85f, 0.85f, 0.85f });

		//Sphere* sphere_ptr2 = new Sphere(Point3(34, 12, 13), 12);
		//sphere_ptr2->SetMaterial(matte_ptr2);
		//m_Scene->AddObject(sphere_ptr2);


		//// medium sphere

		//Sphere* sphere_ptr3 = new Sphere(Point3(-7, 15, 42), 16);
		//sphere_ptr3->SetMaterial(reflective_ptr);
		//m_Scene->AddObject(sphere_ptr3);


		//// cylinder

		////double bottom = 0.0;
		////double top = 85;
		////double radius = 22;
		////SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
		////cylinder_ptr->set_material(reflective_ptr);
		////add_object(cylinder_ptr);


		//// box

		//Matte* matte_ptr5 = new Matte;
		//matte_ptr5->SetKa(ka);
		//matte_ptr5->SetKd(0.5f);
		//matte_ptr5->SetCd({ 0.95f, 0.95f, 0.95f});

		//Box* box_ptr = new Box(Point3(-35, 0, -110), Point3(-25, 60, 65));
		//box_ptr->SetMaterial(matte_ptr5);
		//m_Scene->AddObject(box_ptr);


		//// ground plane

		//Matte* matte_ptr6 = new Matte;
		//matte_ptr6->SetKa(0.15f);
		//matte_ptr6->SetKd(0.5f);
		//matte_ptr6->SetCd({ 0.7f, 0.7f, 0.7f });

		//Plane* plane_ptr = new Plane(Point3(0, 0.01f, 0), Vector(0, 1, 0));
		//plane_ptr->SetMaterial(matte_ptr6);
		//m_Scene->AddObject(plane_ptr);

		//float radius = 23.0f;
		//Sphere* sphere_ptr1 = new Sphere(Point3(38, radius, -25), radius);
		//sphere_ptr1->SetMaterial(reflective_ptr1);
		//m_Scene->AddObject(sphere_ptr1);

		//// orange non-reflective sphere

		//Matte* matte_ptr1 = new Matte;
		//matte_ptr1->SetKa(0.45f);
		//matte_ptr1->SetKd(0.75f);
		//matte_ptr1->SetCd({ 0.75f, 0.25f, 0.0f });   // orange

		//Sphere* sphere_ptr2 = new Sphere(Point3(-7, 10, 42), 20);
		//sphere_ptr2->SetMaterial(matte_ptr1);
		//m_Scene->AddObject(sphere_ptr2);


		//// sphere on top of box

		//Reflective* reflective_ptr2 = new Reflective;
		//reflective_ptr2->SetKa(0.35f);
		//reflective_ptr2->SetKd(0.75f);
		//reflective_ptr2->SetCd(BLACK);
		//reflective_ptr2->SetKs(0.0f);		// default value
		//reflective_ptr2->SetExp(1.0f);		// default value, but irrelevant in this case
		//reflective_ptr2->SetKr(0.75f);
		//reflective_ptr2->SetCr(WHITE);

		//Sphere* sphere_ptr3 = new Sphere(Point3(-30, 59, 35), 20);
		//sphere_ptr3->SetMaterial(reflective_ptr2);
		//m_Scene->AddObject(sphere_ptr3);

		//// cylinder

		//Reflective* reflective_ptr3 = new Reflective;
		//reflective_ptr3->SetKa(0.35f);
		//reflective_ptr3->SetKd(0.5f);
		//reflective_ptr3->SetCd({ 0, 0.5f, 0.75f });   // cyan
		//reflective_ptr3->SetKs(0.2f);
		//reflective_ptr3->SetExp(100.0f);
		//reflective_ptr3->SetKr(0.75f);
		//reflective_ptr3->SetCr(WHITE);

		////float bottom = 0.0f;
		////float top = 85;
		////float cylinder_radius = 22;

		//// box

		//Matte* matte_ptr2 = new Matte;
		//matte_ptr2->SetKa(0.15f);
		//matte_ptr2->SetKd(0.5f);
		//matte_ptr2->SetCd({ 0.75f, 1.0f, 0.75 });   // light green

		//Box* box_ptr = new Box(Point3(-35, 0, -110), Point3(-25, 60, 65));
		//box_ptr->SetMaterial(matte_ptr2);
		//m_Scene->AddObject(box_ptr);


		//// ground plane

		//Matte* sv_matte_ptr = new Matte;
		//sv_matte_ptr->SetKa(0.30f);
		//sv_matte_ptr->SetKd(0.9f);
		//sv_matte_ptr->SetCd(WHITE);

		//Plane* plane_ptr = new Plane(Point3{}, Vector(0, 1, 0));
		//plane_ptr->SetMaterial(sv_matte_ptr);
		//m_Scene->AddObject(plane_ptr);

		//////////////////////////////////////////////////////////////////////////
		//EnvironmentLight
		//////////////////////////////////////////////////////////////////////////
		//float ka = 0.2f;  	// common ambient reflection coefficient

		//// large sphere

		//Matte* matte_ptr1 = new Matte;
		//matte_ptr1->SetKa(ka);
		//matte_ptr1->SetKd(0.60f);
		//matte_ptr1->SetCd({ 0.75f });

		//Sphere* sphere_ptr1 = new Sphere(Point3(-10, 20, -10), 20);
		//sphere_ptr1->SetMaterial(matte_ptr1);
		//m_Scene->AddObject(sphere_ptr1);


		//// small sphere

		//Matte* matte_ptr2 = new Matte;
		//matte_ptr2->SetKa(ka);
		//matte_ptr2->SetKd(0.5f);
		//matte_ptr2->SetCd(0.85f);

		//Sphere* sphere_ptr2 = new Sphere(Point3(34, 12, 13), 12);
		//sphere_ptr2->SetMaterial(matte_ptr2);
		//m_Scene->AddObject(sphere_ptr2);


		//// medium sphere

		//Matte* matte_ptr3 = new Matte;
		//matte_ptr3->SetKa(ka);
		//matte_ptr3->SetKd(0.5f);
		//matte_ptr3->SetCd({ 0.75f });

		//Sphere* sphere_ptr3 = new Sphere(Point3(-7, 15, 42), 16);
		//sphere_ptr3->SetMaterial(matte_ptr3);
		//m_Scene->AddObject(sphere_ptr3);

		//// box

		//Matte* matte_ptr5 = new Matte;
		//matte_ptr5->SetKa(ka);
		//matte_ptr5->SetKd(0.5f);
		//matte_ptr5->SetCd({ 0.95f });

		//Box* box_ptr = new Box(Point3(-35, 0, -110), Point3(-25, 60, 65));
		//box_ptr->SetMaterial(matte_ptr5);
		//m_Scene->AddObject(box_ptr);


		//// ground plane

		//Matte* matte_ptr6 = new Matte;
		//matte_ptr6->SetKa(0.15f);
		//matte_ptr6->SetKd(0.5f);
		//matte_ptr6->SetCd(0.7f);

		//Plane* plane_ptr = new Plane(Point3(0, 0.01f, 0), Vector(0, 1, 0));
		//plane_ptr->SetMaterial(matte_ptr6);
		//m_Scene->AddObject(plane_ptr);

		/************************************************************************/
		/* Area Light                                                           */
		/************************************************************************/
		//CameraDesc desc;
		//desc.eye = { 100, 45, 100 };
		//desc.lookAt = { -10, 40, 0 };
		//m_Camera = new PinholeCamera(desc, 1.0f, 400);

		//Emissive* emissive_ptr = new Emissive;
		//emissive_ptr->SetLs(0.6f);
		//emissive_ptr->SetCe({0.9f});

		//// define a rectangle for the rectangular light

		//float width = 4.0f;				// for Figure 18.4(a) & (b)
		//float height = 4.0f;
		////	float width = 2.0;				// for Figure 18.4(c)
		////	float height = 2.0;
		//Point3 center(0.0f, 7.0f, -7.0f);	// center of each area light (rectangular, disk, and spherical)
		//Point3 p0(-0.5f * width, center.y - 0.5f * height, center.z);
		//Vector a(width, 0.0f, 0.0f);
		//Vector b(0.0f, height, 0.0f);

		////Rectangle* rectangle_ptr = new Rectangle(p0, a, b);
		////rectangle_ptr->SetMaterial(emissive_ptr);
		////rectangle_ptr->SetSampler(sampler_ptr);
		////rectangle_ptr->SetShadow(false);
		////m_Scene->AddObject(rectangle_ptr);


		//EnvironmentLight* area_light_ptr = new EnvironmentLight;
		////area_light_ptr->SetPosition({ 5.0f, 5.0f, 5.0f });
		////area_light_ptr->SetLs(5.0f);
		////area_light_ptr->SetC({ 0.75f, 0.25f, 0.1f });
		////area_light_ptr->SetObject(rectangle_ptr);
		//area_light_ptr->SetSampler(sampler_ptr);
		//area_light_ptr->SetMaterial(emissive_ptr);
		//area_light_ptr->SetShadow(true);
		//m_Scene->AddLight(area_light_ptr);


		//// Four axis aligned boxes

		//float box_width = 1.0f; 		// x dimension
		//float box_depth = 1.0f; 		// z dimension
		//float box_height = 4.5f; 		// y dimension
		//float gap = 3.0f;

		//Matte* matte_ptr1 = new Matte;
		//matte_ptr1->SetKa(0.25f);
		//matte_ptr1->SetKd(0.75f);
		//matte_ptr1->SetCd({ 0.4f, 0.7f, 0.4f });     // green

		//Box* box_ptr0 = new Box(Point3(-1.5f * gap - 2.0f * box_width, 0.0f, -0.5f * box_depth),
		//	Point3(-1.5f * gap - box_width, box_height, 0.5f * box_depth));
		//box_ptr0->SetMaterial(matte_ptr1);
		//m_Scene->AddObject(box_ptr0);

		//Box* box_ptr1 = new Box(Point3(-0.5f * gap - box_width, 0.0f, -0.5f * box_depth),
		//	Point3(-0.5f * gap, box_height, 0.5f * box_depth));
		//box_ptr1->SetMaterial(matte_ptr1);
		//m_Scene->AddObject(box_ptr1);

		//Box* box_ptr2 = new Box(Point3(0.5f * gap, 0.0f, -0.5f * box_depth),
		//	Point3(0.5f * gap + box_width, box_height, 0.5f * box_depth));
		//box_ptr2->SetMaterial(matte_ptr1);
		//m_Scene->AddObject(box_ptr2);

		//Box* box_ptr3 = new Box(Point3(1.5f * gap + box_width, 0.0f, -0.5f * box_depth),
		//	Point3(1.5f * gap + 2.0f * box_width, box_height, 0.5f * box_depth));
		//box_ptr3->SetMaterial(matte_ptr1);
		//m_Scene->AddObject(box_ptr3);

		//Box* box_ptr4 = new Box(Point3(1.5f * gap + box_width, 0.0f, -2.5f * box_depth),
		//	Point3(1.5f * gap + 2.0f * box_width, box_height * 1.5f, -1.0f * box_depth));
		//box_ptr4->SetMaterial(matte_ptr1);
		//m_Scene->AddObject(box_ptr4);


		//// ground plane

		//Matte* matte_ptr2 = new Matte;
		//matte_ptr2->SetKa(0.1f);
		//matte_ptr2->SetKd(0.90f);
		//matte_ptr2->SetCd(WHITE);

		//Plane* plane_ptr = new Plane(Point3(0.0f), Vector(0, 1, 0));
		//plane_ptr->SetMaterial(matte_ptr2);
		//m_Scene->AddObject(plane_ptr);

		/************************************************************************/
		/* Previous Scene                                                       */
		/************************************************************************/

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

	bool Renderer::Render()
	{
		return m_Camera->Render(this);
	}

}