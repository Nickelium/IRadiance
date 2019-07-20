#include "pch.h"
#include "FreeCamera.h"

#pragma warning (push)
#pragma warning (disable:4127)
#pragma warning (disable:4201)
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#pragma warning (pop)


namespace IRadiance
{
	FreeCamera::FreeCamera(float _speed, float _sensitivity)
		: Perspective(16.0f / 9.0f, 60.0f), 
		m_MouseSpeed(_speed),
		m_MouseSensitivity(_sensitivity)
	{

	}

	void FreeCamera::Update(DataTime _time)
	{
		glm::vec3 direction(0, 0, 0);
		if (Input::IsKeyPressed(IRAD_KEY_A))
			direction += glm::vec3(-1, 0, 0);
		else if (Input::IsKeyPressed(IRAD_KEY_D))
			direction += glm::vec3(1, 0, 0);
		if (Input::IsKeyPressed(IRAD_KEY_W))
			direction += glm::vec3(0, 0, -1);
		else if (Input::IsKeyPressed(IRAD_KEY_S))
			direction += glm::vec3(0, 0, 1);
		if (Input::IsKeyPressed(IRAD_KEY_SPACE))
			direction += glm::vec3(0, 1, 0);
		else if (Input::IsKeyPressed(IRAD_KEY_LEFT_ALT))
			direction += glm::vec3(0, -1, 0);
		if (glm::length(direction) > 1e-3f)
		{
			glm::mat4 R = glm::eulerAngleXYZ(
				glm::radians(rotation.x),
				glm::radians(rotation.y),
				glm::radians(rotation.z));
			direction = R * glm::vec4(glm::normalize(direction), 0.0f);
		}
		position += direction * _time.dt * m_MouseSpeed;

		glm::vec2 mousePos = Input::GetMousePosition();
		if (Input::IsMouseButtonPressed(IRAD_MOUSE_BUTTON_RIGHT))
		{
			glm::vec2 deltaPos = mousePos - m_PrevMousePos;
			deltaPos *= m_MouseSensitivity;

			rotation.y += deltaPos.x;
			rotation.x += deltaPos.y;
		}
		m_PrevMousePos = mousePos;
		

		UpdateMatrices();
	}

}