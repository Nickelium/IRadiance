#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace IRadiance
{
	struct Transform
	{
		glm::vec3 position {0,0,0};
		glm::vec3 rotation {0,0,0};
		glm::vec3 scale {1,1,1};
	};

	class Actor;
	class TransformComponent : public Component
	{
	public:
		TransformComponent(Actor* _actor);

		glm::mat4 GetMatrix() const;
		Transform m_Transform;

		COMPONENT_CLASS(TransformComponent)
	private:
	};
}
