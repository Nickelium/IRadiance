#include <IRadiance.h>

#include <GLFW/glfw3.h>

class ExampleLayer : public IRadiance::BaseLayer
{
	IRadiance::DataTime m_Time;
	IRadiance::Renderer m_Renderer;

	std::thread renderThread;

	int m_NbSamples;

	void CloseRenderThread()
	{
		m_Renderer.Stop();
		if (renderThread.joinable())
			renderThread.join();
	}

	void StartRenderThread()
	{
		m_Renderer.Run();
		renderThread = std::thread(&IRadiance::Renderer::Render, std::ref(m_Renderer));
	}
	
public:
	ExampleLayer(IRadiance::Application* _application)
		: BaseLayer(_application)
	{
		using namespace IRadiance;

		RenderDevice* renderDevice = Locator::Get<RenderDevice>();
		int width = 300;// int(720 * (16.0f / 9.0f));
		int height = 300;
		m_Texture = renderDevice->CreateTexture2D(width, height);

		m_Renderer.Build(m_Texture->GetImageBuffer());
		m_Renderer.Run();
	}

	virtual ~ExampleLayer()
	{
		CloseRenderThread();
	}

	virtual void Update(IRadiance::DataTime _time) 
	{
		m_Time = _time;
	}
	virtual void RenderGUI() 
	{
		using namespace IRadiance;
		ImGui::Begin("Frame Update Information");
		ImGui::Text("	%.3f ms", m_Time.dt * 1000.0f);
		ImGui::Text("	%.1f fps", 1.0f / m_Time.dt);
		ImGui::End();

		ImGui::Begin("Render");
		if (ImGui::Button("Rendering"))
		{
			IRAD_INFO("Starting Rendering ...");
			CloseRenderThread();
			StartRenderThread();
		}
		/*m_NbSamples = m_Renderer.GetNbSamples();
		if (ImGui::InputInt("Number of Samples", &m_NbSamples))
		{
			m_Renderer.SetNbSamples(m_NbSamples);
		}*/
		if (ImGui::Button("Clear"))
		{
			IRAD_INFO("Clearing ImageBuffer");
			CloseRenderThread();
			m_Texture->GetImageBuffer()->Clear();
		}
		if (ImGui::Button("Save As"))
		{
			m_Texture->GetImageBuffer()->Write("output/image");
			IRAD_INFO("Image Saved");
		}
		ImGui::End();
	}

	virtual void OnEvent(IRadiance::Event& /*_event*/) 
	{
	}
};

class SandboxApplication : public IRadiance::Application
{
public:
	SandboxApplication()
		: Application(300, 300)
	{
		using namespace IRadiance;
		IRAD_INFO("Creating Sandbox Application");
		PushLayer(new ExampleLayer(this));
	}

	virtual ~SandboxApplication()
	{
		IRAD_INFO("Destroying Sandbox Application");
	}

	virtual void OnEvent(IRadiance::Event& _event)
	{
		using namespace IRadiance;
		if (_event.GetEventType() == IRadiance::EventType::KeyReleased)
		{
			KeyReleasedEvent& relEvent = (KeyReleasedEvent&)_event;
			if (relEvent.GetKeyCode() == IRAD_KEY_ESCAPE)
				Application::CloseWindow();
		}
	}
private:
};

IRadiance::Application* CreateApplication()
{
	return new SandboxApplication;
}