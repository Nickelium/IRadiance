#include "pch.h"
#include "RenderDevice.h"

#include "IRadiance/Platform/OpenGL/GLRenderDevice.h"
#include "IRadiance/Framework/Renderer/Render.h"

namespace IRadiance
{
	RenderDevice* RenderDevice::Create()
	{
		switch (Render::GetAPI())
		{
			case RenderAPI::API::OPENGL: return new GLRenderDevice;
			case RenderAPI::API::D3D11: IRAD_CORE_ASSERT(false, "RenderAPI:D3D11 not supported"); return nullptr;
		}

		IRAD_CORE_ASSERT(false, "Invalid RenderAPI");
		return nullptr;
	}
}