#include "pch.h"
#include "Renderer.h"

#include "IRadiance/Raytracer/Tracers/SingleObject.h"
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
		m_Tracer = new SingleObject(this);

		AddObject(new Sphere({}, 200.0f));
		m_Sphere.r = 85.0f;
	}

	void Renderer::PreRender()
	{
		coVars.row = 0;
		coVars.col = 0;
	}

	void Renderer::Render()
	{
		ImageBuffer& bufferRef = *m_Buffer;
		Ray ray({}, { 0.0f, 0.0f, -1.0f });
		float x, y;

		for (; coVars.row < m_ViewingPlane.m_VertRes;)
		{
			for (; coVars.col < m_ViewingPlane.m_HorRes;)
			{
				int r = coVars.row;
				int c = coVars.col;

				x = m_ViewingPlane.m_PixelSize * (c - 0.5f * (m_ViewingPlane.m_HorRes - 1.0f));
				y = m_ViewingPlane.m_PixelSize * (r - 0.5f * (m_ViewingPlane.m_VertRes - 1.0f));				ray.o = {x, y, 100.0f};
				RGBSpectrum pixel = m_Tracer->RayTrace(ray);
				bufferRef[r][c] = ToRGBA(pixel);

				++coVars.col;
			}
			coVars.col = 0;
			++coVars.row;
			if (coVars.row % 3 == 0)
				return;
		}
	}

}