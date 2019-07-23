#pragma once

#include "IRadiance/Framework/Core/Input.h"

namespace IRadiance
{
	class Window;
	class WindowsInput : public Input 
	{
	public:
		WindowsInput(Window* _window);
	protected:
		virtual bool IsKeyPressedImpl(int _keyCode) override;
		virtual bool IsMousePressedImpl(int _button) override;
		virtual glm::vec2 GetMousePositionImpl() override;

		Window* m_Window;

	};
}
