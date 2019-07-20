#include "pch.h"
#include "MeshComponent.h"

#include "IRadiance/Framework/Renderer/MeshRender.h"

namespace IRadiance
{

	MeshComponent::MeshComponent(Actor* _actor, MeshRender* _mesh)
		: Component(_actor), m_Mesh(_mesh)
	{
	}

	MeshComponent::~MeshComponent()
	{
		delete m_Mesh;
	}

}