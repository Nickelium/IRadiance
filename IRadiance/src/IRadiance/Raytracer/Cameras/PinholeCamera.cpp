#include "pch.h"
#include "PinholeCamera.h"

#include "IRadiance/Raytracer/Maths/Point2.h"
#include "IRadiance/Raytracer/Maths/Point3.h"

#include "IRadiance/Raytracer/Renderer.h"
#include "IRadiance/Raytracer/Samplers/Sampler.h"
#include "IRadiance/Raytracer/Tracers/Tracer.h"

namespace IRadiance
{

	PinholeCamera::PinholeCamera(const CameraDesc _desc, float _zoom, float _d)
		: Camera(_desc), 
		m_D(_d),
		m_Zoom(_zoom)
	{
	}

	Vector PinholeCamera::GetDirection(const Point2 _p) const
	{
		return Normalize(_p.x * m_U + _p.y * m_V - m_D * m_W);
	}

	bool PinholeCamera::Render(Renderer* _renderer)
	{
		ImageBuffer& bufferRef = *_renderer->GetImageBuffer();
		Ray ray;
		ray.o = m_Eye;
		int depth = 0;
		Point2 pp;
		Point2 sp;

		const Display* display = _renderer->GetDisplay();
		const ToneMapper* toneMapper = _renderer->GetToneMapper();
		const ViewPlane& viewPlane = *_renderer->GetViewPlane();
		const Tracer* tracer = _renderer->GetTracer();
		Timer& timer = _renderer->GetTimer();
		CoVariables& coVars = _renderer->GetCoVariables();
	
		float zoomedPixelSize = viewPlane.m_PixelSize / m_Zoom;

		timer.Start();
		for (; coVars.row < viewPlane.m_VertRes;)
		{
			for (; coVars.col < viewPlane.m_HorRes;)
			{
				int r = coVars.row;
				int c = coVars.col;

				RGBSpectrum L = BLACK;
				for (int p = 0; p < viewPlane.m_NumSamples; ++p)
				{
					sp = viewPlane.GetSampler()->SampleUnitSquare();
					pp.x = zoomedPixelSize * (c - 0.5f * viewPlane.m_HorRes + sp.x);
					pp.y = zoomedPixelSize * (r - 0.5f * viewPlane.m_VertRes + sp.y);
					ray.d = GetDirection(pp);
					L += tracer->RayTrace(ray, depth);
				}
				L /= (float)viewPlane.m_NumSamples;
				L *= m_ExposureTime;

				bufferRef[r][c] = 
					display->ConvertDisplay(toneMapper->ToneMap(L));

				++coVars.col;
			}
			coVars.col = 0;
			++coVars.row;

			timer.Update();
			float dt = timer.GetTotal();
			if (dt >= 1.0f / 15.0f)
				return false;
			//if (coVars.row % 3 == 0)
				//return false;
		}

		return true;
	}

}