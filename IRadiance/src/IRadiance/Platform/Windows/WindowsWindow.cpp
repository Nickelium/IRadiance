#include "pch.h"
#include "WindowsWindow.h"

#include "IRadiance/Framework/Events/ApplicationEvent.h"
#include "IRadiance/Framework/Events/MouseEvent.h"
#include "IRadiance/Framework/Events/KeyEvent.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

#include "IRadiance/Platform/OpenGL/GLContext.h"

namespace IRadiance
{
	static bool s_GLFWInitialized = false;

	//None member function
	void GLFWErrorCallback(int _error, const char* _description)
	{
		IRAD_CORE_ERROR("GLFW Error ({0}): {1}", _error, _description);
	}

	Window* Window::Create(const WindowDesc& _desc)
	{
		return new WindowsWindow(_desc);
	}

	WindowsWindow::WindowsWindow(const WindowDesc& _desc)
	{
		Init(_desc);
		Input::s_Instance = std::make_unique<WindowsInput>(this);
	}

	WindowsWindow::~WindowsWindow()
	{
		Destroy();
	}

	void WindowsWindow::Init(const WindowDesc& _desc)
	{
		m_Data.Title = _desc.Title;
		m_Data.Width = _desc.Width;
		m_Data.Height = _desc.Height;

		IRAD_CORE_INFO("Creating window {0} ({1}, {2})", _desc.Title, _desc.Width, _desc.Height);

		//Initialize once, system might have multiple windows
		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			IRAD_CORE_ASSERT(success, "Failed to intialize GLFW");
			IRAD_CORE_TRACE("{0}", "GLFW Initialized");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		#if defined(DEBUG) || defined(_DEBUG)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif

		m_Window = glfwCreateWindow((int)_desc.Width, (int)_desc.Height, m_Data.Title.c_str(), nullptr, nullptr);
		IRAD_CORE_ASSERT(m_Window, "Window is nullptr");

		CenterWindow();

		m_Context = new GLContext(m_Window);
		m_Context->Init();
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	
		// Set GLFW Callback functions
		glfwSetWindowSizeCallback(m_Window, 
			[](GLFWwindow* _window, int _width, int _height)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);
			data.Width = _width;
			data.Height = _height;

			WindowResizeEvent event(_width, _height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window,
		[](GLFWwindow* _window)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* _window, int _key, int /*_scancode*/, int _action, int /*_mods*/)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);
			switch (_action)
			{
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(_key);
					data.EventCallback(event);
					break;
				}
				case GLFW_PRESS:
				{
					KeyPressedEvent event(_key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(_key, 1);
					data.EventCallback(event);
					break;
				}
				default:break;
			}
		});

		glfwSetCharCallback(m_Window,
			[](GLFWwindow* _window, unsigned int _ch)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);
			KeyTypedEvent event(_ch);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window,
			[](GLFWwindow* _window, int _button, int _action, int /*_mod*/)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);
			switch (_action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(_button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(_button);
				data.EventCallback(event);
				break;
			}
			default:break;
			}
		});

		glfwSetScrollCallback(m_Window, 
			[](GLFWwindow* _window, double _xScroll, double /*yScroll*/)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);

			MouseScrolledEvent event(static_cast<float>(_xScroll));
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, 
			[](GLFWwindow* _window, double _x, double _y)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);
			MouseMovedEvent event(static_cast<float>(_x), static_cast<float>(_y));
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Destroy()
	{
		glfwDestroyWindow(m_Window); 
		glfwTerminate(); //Cause glfw error
		//TEMP
		delete m_Context;
		//s_GLFWInitialized = false;
	}

	bool WindowsWindow::CenterWindow()
	{
		GLFWwindow *window = m_Window;
		GLFWmonitor *monitor = glfwGetPrimaryMonitor();

		if (!monitor)
			return false;

		const GLFWvidmode *mode = glfwGetVideoMode(monitor);
		if (!mode)
			return false;

		int monitorX, monitorY;
		glfwGetMonitorPos(monitor, &monitorX, &monitorY);

		glfwSetWindowPos(window,
			monitorX + (mode->width - m_Data.Width) / 2,
			monitorY + (mode->height - m_Data.Height) / 2);

		return true;
	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool _enabled)
	{
		if (_enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = _enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}