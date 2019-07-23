#pragma once

namespace IRadiance
{
	using ComponentType = std::string;

	class Actor;
	class Component
	{
	public:
		Component(Actor* _actor) : m_Actor(_actor) {}
		virtual ~Component() = default;

		virtual void Init() {}
		virtual void Update() {}

		inline Actor* GetActor() const { return m_Actor; }
		virtual ComponentType GetType() const = 0;
		
	protected:
		Actor* m_Actor;
	};

	#define COMPONENT_CLASS(type)\
		inline static ComponentType GetStaticType() { return #type; }\
		virtual ComponentType GetType() const override { return GetStaticType(); }
}
