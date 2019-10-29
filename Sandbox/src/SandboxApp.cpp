#include <IRadiance.h>

#include <GLFW/glfw3.h>
#include "IRadiance/Platform/OpenGL/GLTexture2D.h"

class RaytracerLayer : public IRadiance::BaseLayer
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
	RaytracerLayer(IRadiance::Application* _application)
		: BaseLayer(_application)
	{
		using namespace IRadiance;

		RenderDevice* renderDevice = Locator::Get<RenderDevice>();
		int width = 300;// int(720 * (16.0f / 9.0f));
		int height = width;
		m_Texture = renderDevice->CreateWritableTexture2D(width, height);

		m_Renderer.Build(m_Texture->GetImageBuffer());
		m_Renderer.Run();
	}

	virtual ~RaytracerLayer()
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

class ShaderDifferenceLayer : public IRadiance::Layer
{
	IRadiance::MeshRender* m_QuadRender;
	IRadiance::Texture2D* m_Texture1;
	IRadiance::Texture2D* m_Texture2;

	IRadiance::Texture2D* m_DefaultTexture;
public:
	ShaderDifferenceLayer(IRadiance::Application* _application)
		: Layer(_application)
	{
		using namespace IRadiance;
		RenderDevice* renderDevice = Locator::Get<RenderDevice>();

		std::string vertexShader = ReadFile("res/shaders/QuadDiff.vs");
		std::string fragmentShader = ReadFile("res/shaders/QuadDiff.fs");
		Shader* shader = renderDevice->CreateShader(vertexShader, fragmentShader);
		m_QuadRender = new MeshRender(CreateQuad(), shader);

		m_DefaultTexture = renderDevice->CreateTexture2D("res/textures/checkerboard.tga");

		m_Texture1 = renderDevice->CreateWritableTexture2D("res/textures/1.jpg");
		m_Texture2 = renderDevice->CreateWritableTexture2D("res/textures/2.png");

		RenderCommand::SetClearColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	}

	virtual ~ShaderDifferenceLayer()
	{
		delete m_DefaultTexture;
		delete m_Texture1;
		delete m_Texture2;
		delete m_QuadRender;
	}

	virtual void Render() override
	{
		using namespace IRadiance;
		RenderCommand::Clear();

		Render::Begin();
		{
			RenderCommand::Clear();

			int slot1 = 0;
			if (m_Texture1)
			{
				m_Texture1->Bind(slot1);
				m_Texture1->Update();
			}
			m_QuadRender->GetShader()->SetUniformInt("u_Texture1", slot1);
			int slot2 = 1;
			if (m_Texture2)
			{
				m_Texture2->Bind(slot2);
				m_Texture2->Update();
			}
			m_QuadRender->GetShader()->SetUniformInt("u_Texture2", slot2);

			Render::Submit(m_QuadRender);
		}
		Render::End();
	}
	virtual void RenderGUI() override
	{
		using namespace IRadiance;
		ImGui::Begin("Image Comparison");
		if (ImGui::CollapsingHeader("Texture 1", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
			ImGui::Image(m_Texture1 ? 
				(void*)dynamic_cast<GLAccessibleTexture2D*>(m_Texture1)->m_Handle :
				(void*)dynamic_cast<GLTexture2D*>(m_DefaultTexture)->m_Handle, ImVec2(64, 64),
				{ 0, 1 }, { 1,0 });
			ImGui::PopStyleVar();

			if (ImGui::IsItemClicked())
			{
				FileDialog* fd = Locator::Get<FileDialog>();
				std::string fileName;
				if (fd->OpenFile(fileName))
				{
					RenderDevice* rd = Locator::Get<RenderDevice>();
					delete m_Texture1;
					m_Texture1 = rd->CreateWritableTexture2D(fileName);
					IRAD_INFO("Loading Texture: {0}", fileName);
				}
			}
		}
		if (ImGui::CollapsingHeader("Texture 2", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
			ImGui::Image(m_Texture2 ?
				(void*)dynamic_cast<GLAccessibleTexture2D*>(m_Texture2)->m_Handle :
				(void*)dynamic_cast<GLTexture2D*>(m_DefaultTexture)->m_Handle, ImVec2(64, 64),
				{ 0, 1 }, {1,0});
			ImGui::PopStyleVar();

			if (ImGui::IsItemClicked())
			{
				FileDialog* fd = Locator::Get<FileDialog>();
				std::string fileName;
				if (fd->OpenFile(fileName))
				{
					RenderDevice* rd = Locator::Get<RenderDevice>();
					delete m_Texture2;
					m_Texture2 = rd->CreateWritableTexture2D(fileName);
					IRAD_INFO("Loading Texture: {0}", fileName);
				}
			}
			
		}

		ImGui::Separator();

		if (ImGui::Button("Save As"))
		{
			//m_Texture->GetImageBuffer()->Write("output/image");
			m_Texture2->GetImageBuffer()->Clear();
			IRAD_INFO("Image Saved");
		}

		ImGui::End();
	}

	virtual void OnEvent(IRadiance::Event& /*_event*/) override
	{
	}
};

class SandboxApplication : public IRadiance::Application
{
public:
	SandboxApplication()
		: Application(720, 720)
	{
		using namespace IRadiance;
		IRAD_INFO("Creating Sandbox Application");
		//PushLayer(new RaytracerLayer(this));
		PushLayer(new ShaderDifferenceLayer(this));
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