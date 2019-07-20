#include "pch.h"
#include "Render.h"

#include "API/Shader.h"

namespace IRadiance
{
	void Render::Begin()
	{
	}

	void Render::End()
	{
	}

	void Render::Submit(MeshRender* _mesh)
	{
		_mesh->Bind();
		RenderCommand::DrawIndexed(_mesh->GetVertexArray());
	}
}