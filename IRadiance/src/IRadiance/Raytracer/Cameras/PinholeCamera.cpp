#include "pch.h"
#include "PinholeCamera.h"

#include "IRadiance/Raytracer/Maths/Point2.h"
#include "IRadiance/Raytracer/Maths/Point3.h"

#include "IRadiance/Raytracer/Renderer.h"
#include "IRadiance/Raytracer/Samplers/Sampler.h"
#include "IRadiance/Raytracer/Tracers/Tracer.h"

#include "IRadiance/Framework/Utility/DecimalSeparator.h"

#include <omp.h>

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
	
		float zoomedPixelSize = viewPlane.m_PixelSize / m_Zoom;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		for (int row = 0; row < viewPlane.m_VertRes; ++row)
		{
			for (int col = 0; col < viewPlane.m_HorRes; ++col)
			{
				if (!_renderer->IsRunning())
					return true;

				RGBSpectrum L = BLACK;
				//https://stackoverflow.com/questions/11095309/openmp-set-num-threads-is-not-working
				omp_set_dynamic(0);     // Explicitly disable dynamic teams
				omp_set_num_threads(1); // Use 4 threads for all consecutive parallel regions
				#pragma omp parallel for schedule(dynamic)
				for (int p = 0; p < viewPlane.m_NumSamples; ++p)
				{
					sp = viewPlane.GetSampler()->SampleUnitSquare();
					pp.x = zoomedPixelSize * (col - 0.5f * viewPlane.m_HorRes + sp.x);
					pp.y = zoomedPixelSize * (row - 0.5f * viewPlane.m_VertRes + sp.y);
					ray.d = GetDirection(pp);
					L += tracer->RayTrace(ray, depth);
				}
				L /= (float)viewPlane.m_NumSamples;
				L *= m_ExposureTime;

				bufferRef[row][col] = 
					display->ConvertDisplay(toneMapper->ToneMap(L));
			}
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		IRAD_INFO("Rendering Completed ...");
		std::stringstream ss;
		ss.imbue(std::locale(std::cout.getloc(), new DecimalSeparator<char>(',')));
		ss << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() * 1e-6f /*<< "[s]"*/ << std::endl;
		IRAD_INFO(ss.str());
		return true;
	}

}