#include "pch.h"
#include "Camera.h"

namespace IRadiance
{

	Camera::Camera(const CameraDesc& _desc /*= {}*/)
		: m_Eye(_desc.eye), m_LookAt(_desc.lookAt),
		m_RollAngle(_desc.rollAngle),  
		m_Up(_desc.up),
		m_ExposureTime(_desc.exposureTime)
	{
		ComputeONB();
	}

	void Camera::ComputeONB()
	{
		if (m_Eye.x == m_LookAt.x && m_Eye.z == m_LookAt.z && m_Eye.y > m_LookAt.y)
		{ // camera looking vertically down
			m_U = Vector(0, 0, 1);
			m_V = Vector(1, 0, 0);
			m_W = Vector(0, 1, 0);
			return;
		}

		if (m_Eye.x == m_LookAt.x && m_Eye.z == m_LookAt.z && m_Eye.y < m_LookAt.y)
		{ // camera looking vertically up
			m_U = Vector(1, 0, 0);
			m_V = Vector(0, 0, 1);
			m_W = Vector(0, -1, 0);
			return;
		}

		m_W = Normalize(m_Eye - m_LookAt);
		m_U = Normalize(Cross(m_Up, m_W));
		m_V = Cross(m_W, m_U);

	}

}