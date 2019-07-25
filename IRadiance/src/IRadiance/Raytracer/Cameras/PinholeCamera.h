#pragma once

#include "Camera.h"
#include "IRadiance/Raytracer/Maths/Point2.h"

namespace IRadiance
{
	class PinholeCamera : public Camera
	{
	public:
		PinholeCamera(const CameraDesc _desc = {}, float _zoom = 1, float _d = 100);

		Vector GetDirection(const Point2 _p) const;

		inline void SetViewDistance(float _d) { m_D = _d; }
		inline void SetZoom(float _zoom) { m_Zoom = _zoom; }

		virtual bool Render(Renderer* _renderer) override;

	private:
		float m_D;
		float m_Zoom;
	};

}
