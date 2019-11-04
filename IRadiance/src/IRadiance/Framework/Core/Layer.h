#pragma once

#include "IRadiance/Framework/Events/Event.h"
#include "IRadiance/Framework/Renderer/Scene.h"

namespace IRadiance
{
	class Application;
	/**
	 * Should be subclassed
	 */
	class Layer
	{
	public:
		Layer(Application* _application, Scene* _scene = nullptr);
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void Update(DataTime /*_time*/) {}
		virtual void Render() {}
		virtual void RenderGUI() {}

		virtual void OnEvent(Event& /*_event*/) {}

		inline void Activate() { m_IsActive = true; }
		inline void Deactivate() { m_IsActive = false; }
		inline bool IsActive() const { return m_IsActive; }

	protected:
		Application* m_Application;
		Scene* m_Scene;

		bool m_IsActive = true;
	};
}