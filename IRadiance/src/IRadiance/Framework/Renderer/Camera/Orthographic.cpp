#include "pch.h"
#include "Orthographic.h"

#pragma warning (push)
#pragma warning (disable:4127)
#pragma warning (disable:4201)
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#pragma warning (pop)

namespace IRadiance
{
	Orthographic::Orthographic(
		float _left, float _right,
		float _bottom, float _top,
		float _near /*= 1*/, float _far /*= 100*/)
		: m_Left(_left), m_Right(_right),
		m_Bottom(_bottom), m_Top(_top),
		m_Near(_near), m_Far(_far)
	{
		m_ProjectionMatrix = glm::ortho(_left, _right, _bottom, _top, _near, _far);
		UpdateMatrices();
	}

	void Orthographic::Update(DataTime _time)
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
		if (glm::length(direction) > 1e-3f)
			direction = glm::normalize(direction);
		position += direction * _time.dt;

		UpdateMatrices();
	}

	void Orthographic::UpdateMatrices()
	{
		glm::mat4 R = glm::eulerAngleXYZ(
			glm::radians(rotation.x),
			glm::radians(rotation.y),
			glm::radians(rotation.z));
		glm::vec3 forward = R * glm::vec4(0, 0, -1, 0);
		glm::vec3 up = R * glm::vec4(0, 1, 0, 0);
		m_ViewMatrix = glm::lookAt(position, position + forward, up);
		//m_ViewMatrix = glm::mat4(1.0f);
		//glm::mat4 T = glm::translate(glm::mat4(1.0f), m_Position);
		//glm::mat4 R = glm::rotate()

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}