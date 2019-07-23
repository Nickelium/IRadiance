#pragma once

#include "Camera.h"

namespace IRadiance
{
	class Orthographic : public Camera
	{
	public:
		Orthographic(float _left, float _right, float _bottom, float _top, float _near = 1, float _far = 100);
		virtual void Update(DataTime _time) override;
	private:
		void UpdateMatrices();

		float m_Left, m_Right;
		float m_Bottom, m_Top;
		float m_Near, m_Far;
	};
}