#pragma once

#include "API/RenderCommand.h"
#include "Camera/Camera.h"
#include "MeshRender.h"

namespace IRadiance
{
	class Render
	{
	public:
		static void Begin();
		static void End();

		static void Submit(MeshRender* _mesh);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); };
	private:
	};
}
