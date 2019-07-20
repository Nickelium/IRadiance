#include "pch.h"
#include "GLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace IRadiance
{
	void GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei /*length*/, const GLchar *message,
		const void * /*userParam*/)
	{
		// ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

		IRAD_CORE_FATAL("--- GL ERROR ---");
		IRAD_CORE_FATAL("  Message: {0}", message);

		switch (source)
		{
		case GL_DEBUG_SOURCE_API:             IRAD_CORE_FATAL("  Source: API"); break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   IRAD_CORE_FATAL("  Source: Window System"); break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: IRAD_CORE_FATAL("  Source: Shader Compiler"); break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     IRAD_CORE_FATAL("  Source: Third Party"); break;
		case GL_DEBUG_SOURCE_APPLICATION:     IRAD_CORE_FATAL("  Source: Application"); break;
		case GL_DEBUG_SOURCE_OTHER:           IRAD_CORE_FATAL("  Source: Other"); break;
		} 

		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:               IRAD_CORE_FATAL("  Type: Error"); break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: IRAD_CORE_FATAL("  Type: Deprecated Behaviour"); break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  IRAD_CORE_FATAL("  Type: Undefined Behaviour"); break;
		case GL_DEBUG_TYPE_PORTABILITY:         IRAD_CORE_FATAL("  Type: Portability"); break;
		case GL_DEBUG_TYPE_PERFORMANCE:         IRAD_CORE_FATAL("  Type: Performance"); break;
		case GL_DEBUG_TYPE_MARKER:              IRAD_CORE_FATAL("  Type: Marker"); break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          IRAD_CORE_FATAL("  Type: Push Group"); break;
		case GL_DEBUG_TYPE_POP_GROUP:           IRAD_CORE_FATAL("  Type: Pop Group"); break;
		case GL_DEBUG_TYPE_OTHER:               IRAD_CORE_FATAL("  Type: Other"); break;
		} 

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:			IRAD_CORE_FATAL("  Severity: high"); break;
		case GL_DEBUG_SEVERITY_MEDIUM:			IRAD_CORE_FATAL("  Severity: medium"); break;
		case GL_DEBUG_SEVERITY_LOW:				IRAD_CORE_FATAL("  Severity: low"); break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	IRAD_CORE_FATAL("  Severity: notification"); break;
		} 

		IRAD_CORE_ASSERT(false, "--- GL ERROR ---");
	}

	GLContext::GLContext(GLFWwindow* _windowHandle)
		: m_WindowHandle(_windowHandle)
	{
		IRAD_CORE_ASSERT(m_WindowHandle, "Windows Handle is nullptr");	
	}

	void GLContext::Init()
	{
		IRAD_CORE_ASSERT(m_WindowHandle, "Windows Handle is nullptr");
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		IRAD_CORE_ASSERT(status, "Failed to initialize Glad");
		IRAD_CORE_TRACE("{0}", "Glad Initialized");

		IRAD_CORE_INFO("OpenGL GPU:");
		IRAD_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		IRAD_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		IRAD_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		#if defined(DEBUG) || defined(_DEBUG)
		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			// Otherwise won't indicate at exact glCall
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(GLDebugCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
		#endif

	}

	void GLContext::SwapBuffers()
	{
		IRAD_CORE_ASSERT(m_WindowHandle, "Windows Handle is nullptr");
		glfwSwapBuffers(m_WindowHandle);
	}

}