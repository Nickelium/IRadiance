#pragma once

#include "Component.h"
#include "TransformComponent.h"

namespace IRadiance
{
	class Actor
	{
		using ComponentMap = std::unordered_map<ComponentType, Component*>;
	public:
		Actor();
		~Actor();
		
		void AddComponent(Component* _component);

		template <typename TypeComponent>
		TypeComponent* GetComponent() 
		{
			ComponentType type = TypeComponent::GetStaticType();
			if (m_Components.find(type) == m_Components.end())
				return nullptr;
			return dynamic_cast<TypeComponent*>(m_Components[type]);
		}

		template <>
		TransformComponent* GetComponent() 
		{
			return &m_TransformComponent;
		}

	private:
		ComponentMap m_Components;
		TransformComponent m_TransformComponent;
	};
}