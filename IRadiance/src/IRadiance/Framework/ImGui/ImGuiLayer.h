#pragma once

#include "IRadiance/Framework/Core/Layer.h"

#include "IRadiance/Framework/Events/ApplicationEvent.h"
#include "IRadiance/Framework/Events/MouseEvent.h"
#include "IRadiance/Framework/Events/KeyEvent.h"

namespace IRadiance
{
	class Application;
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(Application* _application);
		virtual ~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void RenderGUI() override;

		void Begin();
		void End();
		
	private:
	};
}
