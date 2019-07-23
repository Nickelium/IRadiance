#pragma once

namespace IRadiance
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(int _keyCode) 
		{ return s_Instance->IsKeyPressedImpl(_keyCode); }
		inline static bool IsMouseButtonPressed(int _button) 
		{ return s_Instance->IsMousePressedImpl(_button); }
		inline static float GetMouseX() { return GetMousePosition().x; }
		inline static float GetMouseY() { return GetMousePosition().y; }
		inline static glm::vec2 GetMousePosition() 
		{ return s_Instance->GetMousePositionImpl(); }

		static std::unique_ptr<Input> s_Instance;
	protected:
		virtual bool IsKeyPressedImpl(int _keyCode) = 0;
		virtual bool IsMousePressedImpl(int _button) = 0;
		virtual glm::vec2 GetMousePositionImpl() = 0;
	private: 
	};
}
