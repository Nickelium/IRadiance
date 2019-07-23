#include "pch.h"
#include "Renderer.h"

#include "IRadiance/Raytracer/Tracers/SingleObject.h"
#include "IRadiance/Raytracer/Tracers/MultiObject.h"

#include "IRadiance/Raytracer/Geometry/Sphere.h"
#include "IRadiance/Raytracer/Geometry/Plane.h"

#include "IRadiance/Framework/Renderer/ImageBuffer.h"

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

		m_BackColor = WHITE;
		m_Tracer = new MultiObject(this);

		//AddObject(new Sphere({0.0f, 0.0f, -100.0f}, 100.0f));
		//AddObject(new Sphere({ +75, 0, -100.0f}, 75));
		//AddObject(new Sphere({ -75, 0, -100.0f}, 75));

		Sphere* sphere_ptr = new Sphere;
		sphere_ptr->SetCenter({ 0, -25, 0 });
		sphere_ptr->SetRadius(80);
		sphere_ptr->SetColor({ 1, 0, 0 }); // red
		AddObject(sphere_ptr);
		// use constructor to set sphere center and radius
		sphere_ptr = new Sphere(Point(0, 30, 0), 60);
		sphere_ptr->SetColor({1, 1, 0}); // yellow
		AddObject(sphere_ptr);
		Plane* plane_ptr = new Plane(Point(0, 0, 0), Normal(0, 1, 1));
		plane_ptr->SetColor({ 168/255.0f, 212 / 255.0f, 211.0f / 255.0f }); // dark green
		AddObject(plane_ptr);
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
		float x, y;
		int n = 4;
		m_Timer.Start();
		for (; coVars.row < m_ViewingPlane.m_VertRes;)
		{
			for (; coVars.col < m_ViewingPlane.m_HorRes;)
			{
				int r = coVars.row;
				int c = coVars.col;

				RGBSpectrum pixel = BLACK;
				for (int p = 0; p < n ;++p)
				{
					for (int q = 0; q < n; ++q)
					{

						x = m_ViewingPlane.m_PixelSize *
							(c - 0.5f * m_ViewingPlane.m_HorRes + (q + 0.5f) / n);
						y = m_ViewingPlane.m_PixelSize *							(r - 0.5f * m_ViewingPlane.m_VertRes + (p + 0.5f) / n);						ray.o = { x, y, 100.0f };
						pixel += m_Tracer->RayTrace(ray);
					}
				}
				pixel /= float(n * n);
			
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