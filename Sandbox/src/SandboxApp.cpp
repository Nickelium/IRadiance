#include <IRadiance.h>

#include <GLFW/glfw3.h>

class ExampleLayer : public IRadiance::BaseLayer
{
	IRadiance::DataTime m_Time;
	IRadiance::Renderer m_World;
	
	bool render = false;
public:
	ExampleLayer(IRadiance::Application* _application)
		: BaseLayer(_application)
	{
		using namespace IRadiance;

		RenderDevice* renderDevice = Locator::Get<RenderDevice>();
		int width = 600;
		int height = int(width * (9.0f / 16.0f));
		m_Texture = renderDevice->CreateTexture2D(width, height);

		m_World.Build(m_Texture->GetImageBuffer());
		m_World.PreRender();
	}

	virtual ~ExampleLayer()
	{

	}

	virtual void Update(IRadiance::DataTime _time) 
	{
		using namespace IRadiance;
		if (render)
		{
			bool completed = m_World.Render();
			if (completed)
			{
				IRAD_INFO("Rendering Completed ...");
				render = false;
			}
		}

		m_Time = _time;
	}
	virtual void RenderGUI() 
	{
		ImGui::Begin("Frame Update Information");
		ImGui::Text("	%.3f ms", m_Time.dt * 1000.0f);
		ImGui::Text("	%.1f fps", 1.0f / m_Time.dt);
		ImGui::End();

		ImGui::Begin("Render");
		if (ImGui::Button("Rendering"))
		{
			IRAD_INFO("Starting Rendering ...");
			render = true;
			m_World.PreRender();
		}
		if (ImGui::Button("Clear"))
		{
			IRAD_INFO("Clearing ImageBuffer");
			m_Texture->GetImageBuffer()->Clear();
			render = false;
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