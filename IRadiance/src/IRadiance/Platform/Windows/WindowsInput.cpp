#include "pch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

#include "IRadiance/Framework/Core/Application.h"
#include "IRadiance/Framework/Core/Window.h"

namespace IRadiance
{
	std::unique_ptr<Input> Input::s_Instance;

	WindowsInput::WindowsInput(Window* _window)
		: m_Window(_window)
	{
	}

	bool WindowsInput::IsKeyPressedImpl(int _keyCode)
	{
		auto pGLFWWindow = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
		auto state = glfwGetKey(pGLFWWindow, _keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMousePressedImpl(int _button)
	{
		auto pGLFWindow = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
		auto state = glfwGetMouseButton(pGLFWindow, _button);
		return state == GLFW_PRESS;
	}

	glm::vec2 WindowsInput::GetMousePositionImpl()
	{
		auto pGLFWWindow = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
		double x, y;
		glfwGetCursorPos(pGLFWWindow, &x, &y);
		return { static_cast<float>(x), static_cast<float>(y) };
	}

}