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
#include "Geometry/Triangle.h"
#include "Geometry/OpenCylinder.h"
#include "Geometry/ConcaveSphere.h"
#include "Materials/Transparent.h"


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

	void Renderer::BuildCornellBoxData(int _nbSamples)
	{
		m_MaxDepth = 10;

		CameraDesc desc;
		desc.eye = { 27.8f, 27.3f, -80.0f };
		desc.lookAt = desc.eye + Vector{0.0f, 0.0f, 1.0f};
		m_Camera = new PinholeCamera(desc, 1.0f, 418.0f * (720 / 300.0f)/** 2.4f*/);


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
		emissive_ptr->SetCe({ 1.0f, 0.67f, 0.21f });
		emissive_ptr->SetLs(40);

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
		matte_ptr1->SetKd(0.75f);
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
		matte_ptr2->SetKd(0.75f);
		matte_ptr2->SetCd({ 0.025f,0.236f,0.025f });	 // green   from Photoshop
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
		matte_ptr3->SetKd(0.75f);
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

	void Renderer::BuildCornellBox(int _nbSamples)
	{
		m_MaxDepth = 10;

		CameraDesc desc;
		desc.eye = { 27.6f, 27.4f, -80.0f };
		desc.lookAt = { 27.6f, 27.4f, 0.0f };
		m_Camera = new PinholeCamera(desc, 1.0f, 418.0f * (720 / 300.0f)/** 2.4f*/);


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
		CameraDesc desc;
		desc.eye = { -50, 100, 50 };
		desc.lookAt = { 0, 0.0f, 0.0f };
		m_Camera = new PinholeCamera(desc, 1.0f, 8000 /** 2.4f*/);

		// emissive sphere
		Emissive* emissive_ptr = new Emissive;
		emissive_ptr->SetCe({ 0.75f, 1, 0.75f });
		emissive_ptr->SetLs(150.0f);

		Sphere* sphere_ptr = new Sphere(Point3(-2, 10, 12), 1);
		sphere_ptr->SetMaterial(emissive_ptr);
		sphere_ptr->SetSampler(new MultiJitteredSampler(_nbSamples));
		m_Scene->AddObject(sphere_ptr);

		AreaLight* light = new AreaLight;
		light->SetObject(sphere_ptr);
		m_Scene->AddLight(light);


		// reflective open half cylinder

		Reflective* reflective_ptr = new Reflective;
		reflective_ptr->SetKa(0.0f);
		reflective_ptr->SetKd(0.4f);
		reflective_ptr->SetKs(0.0f);
		reflective_ptr->SetExp(1.0f);
		reflective_ptr->SetKr(0.95f);
		reflective_ptr->SetCd({ 1.0f, 0.5f, 0.25f });  // orange 
		reflective_ptr->SetCr({ 1.0f, 0.5f, 0.25f });  // orange 

		float y0 = -1.0f;
		float y1 = 3.0f;
		float radius = 3.0f;
		//float phi_min = 90.0f;
		//float phi_max = 270.0f;

		OpenCylinder* cylinder_ptr = new OpenCylinder(radius, y0, y1);
		cylinder_ptr->SetMaterial(reflective_ptr);
		m_Scene->AddObject(cylinder_ptr);


		// plane

		Matte* matte_ptr = new Matte;
		matte_ptr->SetKa(0.0f);
		matte_ptr->SetKd(0.75f);
		matte_ptr->SetCd({ 0.75f, 0.65f, 0.65f });
		matte_ptr->SetSampler(new MultiJitteredSampler(_nbSamples));

		Plane* plane_ptr = new Plane(Point3(0, -1.0f, 0), Vector(0, 1, 0));
		plane_ptr->SetMaterial(matte_ptr);
		m_Scene->AddObject(plane_ptr);
	}

	void Renderer::BuildReflection(int _nbSamples)
	{
		m_MaxDepth = 10;

		m_BackColor = RGBSpectrum({ 0.0f, 0.0f, 0.0f });

		CameraDesc desc;
		desc.eye = { 100, 45, 100 };
		desc.lookAt = { -10, 40, 0 };
		m_Camera = new PinholeCamera(desc, 1.0f, 525);

		Emissive* emissive_ptr = new Emissive;
		emissive_ptr->SetLs(0.90f);
		emissive_ptr->SetCe({ 1.0f, 1.0f, 0.5f }); 	// lemon yellow

		ConcaveSphere* sphere_ptr = new ConcaveSphere(1000.0f);
		sphere_ptr->SetMaterial(emissive_ptr);
		sphere_ptr->SetShadow(false);
		m_Scene->AddObject(sphere_ptr);

		EnvironmentLight* environment_light_ptr = new EnvironmentLight;
		environment_light_ptr->SetMaterial(emissive_ptr);
		environment_light_ptr->SetSampler(new MultiJitteredSampler(_nbSamples));
		environment_light_ptr->SetShadow(true);
		m_Scene->AddLight(environment_light_ptr);


		// common reflective material for large sphere, medium sphere, and cylinder

		Reflective* reflective_ptr = new Reflective;
		reflective_ptr->SetKa(0.0f);
		reflective_ptr->SetKd(0.0f);
		reflective_ptr->SetCd(BLACK);
		reflective_ptr->SetKs(0.0f);
		reflective_ptr->SetExp(1.0f);
		reflective_ptr->SetKr(0.9f);
		reflective_ptr->SetCr({ 1.0f, 0.75f, 0.5f });   // orange

		Transparent* transparent_ptr = new Transparent;
		transparent_ptr->SetKa(0.0f);
		transparent_ptr->SetKd(0.0f);
		transparent_ptr->SetCd(BLACK);
		transparent_ptr->SetKs(0.0f);
		transparent_ptr->SetExp(1.0f);
		transparent_ptr->SetKr(0.9f);
		transparent_ptr->SetCr({ 1.0f, 0.75f, 0.5f });   // orange
		transparent_ptr->SetIOR(1.0f);

		Material* material = reflective_ptr;

		float ka = 0.2f;  // commom ambient reflection coefficient for other objects

			// large sphere

		Sphere* sphere_ptr1 = new Sphere(Point3(38, 20, -24), 20);
		sphere_ptr1->SetMaterial(material);
		m_Scene->AddObject(sphere_ptr1);


		// small sphere

		Matte* matte_ptr2 = new Matte;
		matte_ptr2->SetKa(ka);
		matte_ptr2->SetKd(0.5f);
		matte_ptr2->SetCd({ 0.85f, 0.85f, 0.85f });
		matte_ptr2->SetSampler(new MultiJitteredSampler(_nbSamples));

		Sphere* sphere_ptr2 = new Sphere(Point3(34, 12, 13), 12);
		sphere_ptr2->SetMaterial(material);
		m_Scene->AddObject(sphere_ptr2);


		// medium sphere

		Sphere* sphere_ptr3 = new Sphere(Point3(-7, 15, 42), 16);
		sphere_ptr3->SetMaterial(material);
		m_Scene->AddObject(sphere_ptr3);


		// cylinder

		float bottom = 0.0f;
		float top = 85;
		float radius = 22;
		OpenCylinder* cylinder_ptr = new OpenCylinder(radius, bottom, top);
		cylinder_ptr->SetMaterial(material);
		m_Scene->AddObject(cylinder_ptr);


		// box

		Matte* matte_ptr5 = new Matte;
		matte_ptr5->SetKa(ka);
		matte_ptr5->SetKd(0.5f);
		matte_ptr5->SetCd({ 0.95f, 0.95f, 0.95f });
		matte_ptr5->SetSampler(new MultiJitteredSampler(_nbSamples));

		Box* box_ptr = new Box(Point3(-35, 0, -110), Point3(-25, 60, 65));
		box_ptr->SetMaterial(matte_ptr5);
		m_Scene->AddObject(box_ptr);


		// ground plane

		Matte* matte_ptr6 = new Matte;
		matte_ptr6->SetKa(0.15f);
		matte_ptr6->SetKd(0.5f);
		matte_ptr6->SetCd({0.7f, 0.7f, 0.7f});
		matte_ptr6->SetSampler(new MultiJitteredSampler(_nbSamples));

		Plane* plane_ptr = new Plane(Point3(0, 0.01f, 0), Vector(0, 1, 0));
		plane_ptr->SetMaterial(matte_ptr6);
		m_Scene->AddObject(plane_ptr);
	}

	void Renderer::BuildRefraction(int _nbSamples)
	{
		m_MaxDepth = 10;

		m_BackColor = BLACK;

		CameraDesc desc;
		desc.eye = { -8, 5.5f, 40 };
		desc.lookAt = { 1, 4, 0 };
		m_Camera = new PinholeCamera(desc, 1.0f, 2400.0f);

		Emissive* emissive_ptr = new Emissive;
		emissive_ptr->SetCe({ 1.0f, 0.73f, 0.4f });
		emissive_ptr->SetLs(500.5f);

		Point3 p0 = Point3({ 8, 10, 4 });
		Vector a = Vector(0.0f, 0.0f, 3.5f);
		Vector b = Vector(3.0f, 0.0f, 0.0f);
		Vector normal = Vector(0.0f, -1.0f, 0.0f);
		Rectangle* light_ptr = new Rectangle(p0, a, b, normal);
		light_ptr->SetMaterial(emissive_ptr);
		m_Scene->AddObject(light_ptr);

		AreaLight* light = new AreaLight;
		light->SetObject(light_ptr);
		light_ptr->SetSampler(new MultiJitteredSampler(_nbSamples));
		light->SetShadow(true);
		m_Scene->AddLight(light);

		//p0 = Point3({ -10, 12, -40 });
		//a = Vector(0.0f, 0.0f, 3.5f);
		//b = Vector(3.0f, 0.0f, 0.0f);
		//normal = Vector(0.0f, -1.0f, 0.0f);
		//Rectangle* light_ptr2 = new Rectangle(p0, a, b, normal);
		//light_ptr2->SetMaterial(emissive_ptr);
		//m_Scene->AddObject(light_ptr2);

		//AreaLight* light2 = new AreaLight;
		//light2->SetObject(light_ptr2);
		//light_ptr2->SetSampler(new MultiJitteredSampler(_nbSamples));
		//light2->SetShadow(true);
		//m_Scene->AddLight(light2);

		// point light 
		/*PointLight* light_ptr1 = new PointLight;
		light_ptr1->SetPosition({ 40, 50, 0 });
		light_ptr1->SetLs(4.5f);
		light_ptr1->SetShadow(true);
		m_Scene->AddLight(light_ptr1);*/


		// point light 
		/*PointLight* light_ptr2 = new PointLight;
		light_ptr2->SetPosition({ -10, 20, 10 });
		light_ptr2->SetLs(4.5);
		light_ptr2->SetShadow(true);
		m_Scene->AddLight(light_ptr2);*/


		// directional light 
		/*DirectionalLight* light_ptr3 = new DirectionalLight;
		light_ptr3->SetDirection({-1, 0, 0});
		light_ptr3->SetLs(4.5f);
		light_ptr3->SetShadow(true);
		m_Scene->AddLight(light_ptr3);*/


		// transparent sphere
		Transparent* glass_ptr = new Transparent;
		glass_ptr->SetKs(0.2f);
		glass_ptr->SetExp(2000.0f);
		glass_ptr->SetIOR(1.0f);
		glass_ptr->SetKr(0.1f);
		glass_ptr->SetCt(WHITE);

		Sphere* sphere_ptr1 = new Sphere(Point3(0.0f, 4.5f, 0.0f), 3.0f);
		sphere_ptr1->SetMaterial(glass_ptr);
		m_Scene->AddObject(sphere_ptr1);


		// red sphere
		Reflective* reflective_ptr = new Reflective;
		reflective_ptr->SetKa(0.3f);
		reflective_ptr->SetKd(0.3f);
		reflective_ptr->SetCd(RED);
		reflective_ptr->SetKs(0.2f);
		reflective_ptr->SetExp(2000.0f);
		reflective_ptr->SetKr(0.25f);
		//reflective_ptr->SetCr(RED);

		Sphere* sphere_ptr2 = new Sphere(Point3(4, 4, -6), 3);
		sphere_ptr2->SetMaterial(reflective_ptr);
		m_Scene->AddObject(sphere_ptr2);

		Matte* matte_ptr = new Matte;
		matte_ptr->SetKa(0.5f);
		matte_ptr->SetKd(0.35f);
		matte_ptr->SetCd(WHITE);
		matte_ptr->SetSampler(new MultiJitteredSampler(_nbSamples));

		// rectangle

		p0 = { -20, 0, -100 };
		a = {0, 0, 120};
		b = { 40, 0, 0 };

		Rectangle* rectangle_ptr = new Rectangle(p0, a, b);
		rectangle_ptr->SetMaterial(matte_ptr);
		m_Scene->AddObject(rectangle_ptr);
	}

	void Renderer::Build(ImageBuffer* _buffer)
	{
		m_Buffer = _buffer;

		m_Display = new Display;
		m_Display->SetGamma(1.9f);
		//m_Display->SetGamma(1.0f);
		//TODO, do actually need to gamma correct because not sampling for texture or so
		//TODO reflection and phong or broken

		m_CollisionHandler = new CollisionHandler(this);
		m_Scene = new SceneGraph;

		m_ToneMapper = new Clamper;

		int num_samples = 100 * 1;   	

		m_ViewingPlane.m_HorRes = m_Buffer->GetWidth();
		m_ViewingPlane.m_VertRes = m_Buffer->GetHeight();
		SetNbSamples(num_samples);

		//m_Tracer = new Whitted(this);
		m_Tracer = new HybridPathTracer(this);

		//BuildCornellBoxData(num_samples); // OK
		//BuildCornellBox(num_samples); // OK
		//BuildCaustics(num_samples); // FACTOR 10 light to approx
		//BuildReflection(num_samples); // OK
		BuildRefraction(num_samples); // OK
		m_Camera->ComputeONB();
	
	}

	bool Renderer::Render()
	{
		return m_Camera->Render(this);
	}

}
