#pragma once

#include "IRadiance/Framework/Renderer/API/RenderAPI.h"

namespace IRadiance
{
	class GLRenderAPI : public RenderAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& _color) override;
		virtual void Clear() override;
		virtual void EnableDepth(bool _enable) override;
		virtual void EnableBlend(bool _enable) override;
		virtual void DrawIndexed(VertexArray* _vertexArray) override;

	private:
	};
}
