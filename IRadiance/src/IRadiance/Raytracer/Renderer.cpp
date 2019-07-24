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

namespace IRadiance
{
	Renderer::~Renderer()
	{
		delete m_Tracer;
		for (Object* object : m_Objects)
			delete object;
	}

	void Renderer::Build(ImageBuffer* _buffer)
	{
		m_Buffer = _buffer;

		m_ViewingPlane.m_HorRes = m_Buffer->GetWidth();
		m_ViewingPlane.m_VertRes = m_Buffer->GetHeight();
		m_ViewingPlane.m_PixelSize = 1.0f;
		m_ViewingPlane.SetGamma(1.0f);
		int nbSamples = 16;
		m_ViewingPlane.SetSampler(new MultiJitteredSampler(nbSamples));
			
		m_BackColor = WHITE;
		m_Tracer = new MultiObject(this);

		AddObject(new Sphere({0.0f, 0.0f, -100.0f}, 100.0f));
		AddObject(new Sphere({ +75, 0, -100.0f}, 75));
		AddObject(new Sphere({ -75, 0, -100.0f}, 75));

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
		//AddObject(plane_ptr);		//AddObject(new Sphere({ 0, -1000, 0 }, 1000));
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
		coVars.row = 0;
		coVars.col = 0;
		m_Timer.Start();
	}

	bool Renderer::Render()
	{
		ImageBuffer& bufferRef = *m_Buffer;
		Ray ray({}, { 0.0f, 0.0f, -1.0f });
		Point2 pp;
		Point2 sp;

		Point3 camOrigin(500, 2, 10);

		m_Timer.Start();
		for (; coVars.row < m_ViewingPlane.m_VertRes;)
		{
			for (; coVars.col < m_ViewingPlane.m_HorRes;)
			{
				int r = coVars.row;
				int c = coVars.col;

				RGBSpectrum pixel = BLACK;
				for (int p = 0; p < m_ViewingPlane.m_NumSamples ;++p)
				{
					sp = m_ViewingPlane.GetSampler()->SampleUnitSquare();
					pp.x = m_ViewingPlane.m_PixelSize *
						(c - 0.5f * m_ViewingPlane.m_HorRes + sp.x);
					pp.y = m_ViewingPlane.m_PixelSize *						(r - 0.5f * m_ViewingPlane.m_VertRes + sp.y);					ray.o = { pp.x, pp.y, 0 } + camOrigin;
					pixel += m_Tracer->RayTrace(ray);
				}
				pixel /= (float)m_ViewingPlane.m_NumSamples;
			
				bufferRef[r][c] = ToRGBA(pixel);

				++coVars.col;
			}
			coVars.col = 0;
			++coVars.row;
			
			m_Timer.Update();
			float dt = m_Timer.GetTotal();
			if (dt >= 1.0f / 15.0f)
				return false;
			//if (coVars.row % 3 == 0)
				//return false;
		}

		return true;
	}

}