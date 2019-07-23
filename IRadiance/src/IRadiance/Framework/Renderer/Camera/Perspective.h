#pragma once

#include "Camera.h"

namespace IRadiance
{
	class Perspective : public Camera
	{
	public:
		Perspective(float _aspectRatio, float _fovV, float _near = 1, float _far = 100);
	protected:
		void UpdateMatrices();

		float m_AspectRatio, m_FovV;
		float m_Near, m_Far;
	};
}
