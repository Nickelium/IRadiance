#pragma once

#include "Component.h"

namespace IRadiance
{
	class MeshRender;
	class MeshComponent : public Component
	{
	public:
		MeshComponent(Actor* _actor, MeshRender* _mesh);
		virtual ~MeshComponent();

		inline MeshRender* GetMesh() const { return m_Mesh; }

		COMPONENT_CLASS(MeshComponent)
	private:
		MeshRender* m_Mesh;
	};
}
