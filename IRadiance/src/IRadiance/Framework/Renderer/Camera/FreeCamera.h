#pragma once

#include "Perspective.h"

namespace IRadiance
{
	class FreeCamera : public Perspective
	{
	public:
		FreeCamera(float _speed = 5.0f, float _sensitivity = 0.1f);
		virtual void Update(DataTime _time) override;
	private:
		float m_MouseSpeed;
		float m_MouseSensitivity;
		
		glm::vec2 m_PrevMousePos;

	};
}