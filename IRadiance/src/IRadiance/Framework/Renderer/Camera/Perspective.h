#pragma once

#include "RenderCamera.h"

namespace IRadiance
{
	class Perspective : public RenderCamera
	{
	public:
		Perspective(float _aspectRatio, float _fovV, float _near = 1, float _far = 100);
	protected:
		void UpdateMatrices();

		float m_AspectRatio, m_FovV;
		float m_Near, m_Far;
	};
}
