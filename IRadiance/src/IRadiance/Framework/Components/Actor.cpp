#include "pch.h"
#include "Actor.h"

namespace IRadiance
{

	Actor::Actor()
		: m_TransformComponent(this)
	{

	}

	Actor::~Actor()
	{
		for (auto& compPair : m_Components)
			delete compPair.second;
	}

	void Actor::AddComponent(Component* _component)
	{
		auto res = m_Components.find(_component->GetType());
		IRAD_CORE_ASSERT(res == m_Components.end(), "Actor already contains ComponentType: {0}", _component->GetType());
		m_Components[_component->GetType()] = _component;
	}

}