#pragma once

#include "IRadiance/Raytracer/Maths/Point3.h"
#include "IRadiance/Raytracer/Maths/Vector.h"

namespace IRadiance
{
	struct CameraDesc
	{
		Point3 eye {0, 0, 100};
		Point3 lookAt{ 0, 0, -100 };
		float rollAngle = 0;
		Vector up{0, 1, 0};
		float exposureTime = 0.85f;
	};

	class Renderer;
	class Camera
	{
	public:
		Camera(const CameraDesc& _desc = {});
		void ComputeONB();

		virtual bool Render(Renderer* _renderer) = 0;
	protected:
		Point3 m_Eye;
		Point3 m_LookAt;
		float m_RollAngle;

		Vector m_U, m_V, m_W;
		Vector m_Up;

		float m_ExposureTime;
	};
}
