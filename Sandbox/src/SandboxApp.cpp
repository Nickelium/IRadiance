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
		int width = 720;// int(720 * (16.0f / 9.0f));
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

void ComputeDifference(const IRadiance::Texture2D* tex1, const IRadiance::Texture2D* tex2, IRadiance::RenderDevice* rd, const std::string& _outFile)
{
	struct RGBAInt
	{
		int r, g, b, a;
	};
	using namespace IRadiance;
	Texture2D* out = rd->CreateWritableTexture2D(tex1->GetWidth(), tex1->GetHeight());
	ImageBuffer& bufferOut = *out->GetImageBuffer();
	ImageBuffer& bufferTex1 = *tex1->GetImageBuffer();
	ImageBuffer& bufferTex2 = *tex2->GetImageBuffer();

	for (int i = 0; i < tex1->GetWidth(); ++i)
	{
		for (int j = 0; j < tex1->GetHeight(); ++j)
		{
			RGBAInt c1;
			c1.r = bufferTex1[j][i].r;
			c1.g = bufferTex1[j][i].g;
			c1.b = bufferTex1[j][i].b;
			RGBAInt c2;
			c2.r = bufferTex2[j][i].r;
			c2.g = bufferTex2[j][i].g;
			c2.b = bufferTex2[j][i].b;
			RGBA r;
			r.r = std::abs(c1.r - c2.r);
			r.g = std::abs(c1.g - c2.g);
			r.b = std::abs(c1.b - c2.b);
			r.a = 0xFF;
			bufferOut[j][i] = r;
		}
	}
	out->GetImageBuffer()->Write(_outFile);
	delete out;
}

float ComputeMSE(const IRadiance::Texture2D* tex1, const IRadiance::Texture2D* tex2)
{
	using namespace IRadiance;

	struct RGBAInt
	{
		int r, g, b, a;
	};
	float RMS = 0.0f;

	ImageBuffer& bufferTex1 = *tex1->GetImageBuffer();
	ImageBuffer& bufferTex2 = *tex2->GetImageBuffer();

	for (int i = 0; i < tex1->GetWidth(); ++i)
	{
		for (int j = 0; j < tex1->GetHeight(); ++j)
		{
			RGBAInt c1;
			c1.r = bufferTex1[j][i].r;
			c1.g = bufferTex1[j][i].g;
			c1.b = bufferTex1[j][i].b;
			RGBAInt c2;
			c2.r = bufferTex2[j][i].r;
			c2.g = bufferTex2[j][i].g;
			c2.b = bufferTex2[j][i].b;
			RGBAInt r;
			r.r = (c1.r - c2.r);
			r.g = (c1.g - c2.g);
			r.b = (c1.b - c2.b);
			
			float avgQuadError = (r.r * r.r + r.g * r.g + r.b * r.b) / 3.0f;
			RMS += avgQuadError;

		}
	}

	RMS /= tex1->GetWidth() * tex1->GetHeight();

	return RMS;
}

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
		m_Texture2 = renderDevice->CreateWritableTexture2D(
			"output/Data/Accuracy/ReferencePOV.png");

		//ComputeDifference(m_Texture1, m_Texture2, renderDevice);
		float MSE1 = ComputeMSE(renderDevice->CreateWritableTexture2D(
			"output/Data/Accuracy/Whitted/Original/16384.jpg"), m_Texture2);
		float MSE2 = 
			ComputeMSE(renderDevice->CreateWritableTexture2D(
			"output/Data/Accuracy/Hybrid/Original/16384.jpg"), m_Texture2);

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
			RenderDevice* rd = Locator::Get<RenderDevice>();
			ComputeDifference(m_Texture1, m_Texture2, rd, "out");
			IRAD_INFO("Image Saved");
		}

		ImGui::End();
	}

	virtual void OnEvent(IRadiance::Event& /*_event*/) override
	{
	}
};

class SelectLayer : public IRadiance::Layer
{
	IRadiance::Layer* m_Layer1;
	IRadiance::Layer* m_Layer2;

	int m_ActiveLayer;
public:
	SelectLayer(IRadiance::Application* _app, IRadiance::Layer* _layer1, IRadiance::Layer* _layer2)
		: Layer(_app), m_Layer1(_layer1), m_Layer2(_layer2)
	{}

	virtual void Update(IRadiance::DataTime)
	{
		if (m_ActiveLayer == 0)
		{
			m_Layer1->Activate();
			m_Layer2->Deactivate();
		}
		else if(m_ActiveLayer == 1)
		{
			m_Layer2->Activate();
			m_Layer1->Deactivate();
		}

	}

	virtual void RenderGUI()
	{
		ImGui::Begin("Program");
		ImGui::RadioButton("Raytracer", &m_ActiveLayer, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Image Difference", &m_ActiveLayer, 1);
		ImGui::End();
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
		Layer* layer1, *layer2;
		PushLayer(layer1 = new RaytracerLayer(this));
		PushLayer(layer2 = new ShaderDifferenceLayer(this));
		PushLayer(new SelectLayer(this, layer1, layer2));
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