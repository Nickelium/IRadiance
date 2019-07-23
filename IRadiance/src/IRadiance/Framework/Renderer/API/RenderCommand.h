#pragma once

#include "RenderAPI.h"

namespace IRadiance
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& _color)
		{
			s_RenderAPI->SetClearColor(_color);
		}
		inline static void Clear()
		{
			s_RenderAPI->Clear();
		}
		
		inline static void EnableDepth(bool _enable)
		{
			s_RenderAPI->EnableDepth(_enable);
		}

		inline static void EnableBlend(bool _enable)
		{
			s_RenderAPI->EnableBlend(_enable);
		}

		inline static void DrawIndexed(VertexArray* _vertexArray)
		{
			s_RenderAPI->DrawIndexed(_vertexArray);
		}
	private:
		static std::unique_ptr<RenderAPI> s_RenderAPI;
	};
}
