#include "pch.h"
#include "Application.h"

#include "IRadiance/Framework/Renderer/API/RenderCommand.h"
#include "IRadiance/Framework/Renderer/API/RenderDevice.h"
#include "IRadiance/Framework/Core/FileDialog.h"

namespace IRadiance
{
	Application::Application(unsigned int _width, unsigned int _height)
		: m_Running(true)
	{
		IRAD_CORE_INFO("Creating Engine Application");
		m_Window = Window::Create({"IRadiance Engine - RAYTRACER", _width, _height});
		m_Window->SetEventCallback(BIND_FN(Application::RootOnEvent));
		Locator::Set(RenderDevice::Create());
		Locator::Set(FileDialog::Create(m_Window));
		m_ImGuiLayer = new ImGuiLayer(this);
		PushOverlay(m_ImGuiLayer);

		RenderCommand::EnableDepth(true);
		RenderCommand::EnableBlend(true);
	}

	Application::~Application()
	{
		IRAD_CORE_INFO("Destroying Engine Application");
		Locator::Destroy();
		delete m_Window;
	}

	void Application::Run()
	{
		Timer timer;
		while (m_Running)
		{
			timer.Update();
			DataTime ts = timer.GetTimeStep();

			Update(ts);
			Render();
			m_Window->Update();
		}
	}

	void Application::Update(DataTime _time)
	{
		for (Layer* layer : m_LayerStack)
			if(layer->IsActive())
				layer->Update(_time);
	}

	void Application::Render()
	{
		for (Layer* layer : m_LayerStack)
			if(layer->IsActive())
				layer->Render();

		m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
			if(layer->IsActive())
				layer->RenderGUI();
		m_ImGuiLayer->End();
	}

	void Application::RootOnEvent(Event& _event)
	{
		EventDispatcher dispatcher(_event);
	
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::OnWindowClose));

		OnEvent(_event);
	
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{

			if (_event.m_Handled)
				break;
			--it;
			if ((*it)->IsActive())
				(*it)->OnEvent(_event);
		}
	}

	bool Application::OnWindowClose(Event& /*_event*/)
	{
		CloseWindow();
		return true;
	}

	void Application::CloseWindow()
	{
		m_Running = false;
	}

	void Application::PushLayer(Layer* _layer)
	{
		m_LayerStack.PushLayer(_layer);
	}

	void Application::PushOverlay(Layer* _layer)
	{
		m_LayerStack.PushOverlay(_layer);
	}
}