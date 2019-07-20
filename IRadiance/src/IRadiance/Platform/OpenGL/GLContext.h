#pragma once

#include "IRadiance/Framework/Renderer/API/GraphicsContext.h"

struct GLFWwindow;
namespace IRadiance
{
	class GLContext : public GraphicsContext
	{
	public:
		GLContext(GLFWwindow* _windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}