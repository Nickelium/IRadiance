#pragma once

#include "IRadiance/Framework/Components/Actor.h"

namespace IRadiance
{
	using Actors = std::vector<Actor*>;
	
	class Scene
	{
		Actors m_Actors;
	public:
		Scene() = default;
		~Scene();

		void Add(Actor* _actor);
		inline const Actors& GetActors() const { return m_Actors; }

		void Update();
	};
}
