#include "pch.h"
#include "TransformComponent.h"

#pragma warning (push)
#pragma warning (disable:4127)
#pragma warning (disable:4201)
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#pragma warning (pop)

namespace IRadiance
{
	TransformComponent::TransformComponent(Actor* _actor)
		: Component(_actor)
	{

	}

	glm::mat4 TransformComponent::GetMatrix() const
	{
		return 	
			glm::translate(glm::mat4(1.0f), m_Transform.position) * 
			glm::eulerAngleXYZ
				(glm::radians(m_Transform.rotation.x),
				glm::radians(m_Transform.rotation.y),
				glm::radians(m_Transform.rotation.z)) *
			glm::scale(glm::mat4(1.0f), m_Transform.scale);
	}

}