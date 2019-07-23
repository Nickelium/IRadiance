#pragma once

#include "IRadiance/Framework/Events/Event.h"

namespace IRadiance
{
	struct WindowDesc
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowDesc(const std::string& title = "IRadiance Engine  ",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void Update() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& _callback) = 0;
		virtual void SetVSync(bool _enabled) = 0;
		virtual bool IsVSync() const = 0;

		//Native implementation
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowDesc& _desc = WindowDesc());
	};

}