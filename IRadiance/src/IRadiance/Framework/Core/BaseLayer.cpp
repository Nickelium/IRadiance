#include "pch.h"
#include "BaseLayer.h"

#include "IRadiance/Framework/Renderer/API/RenderDevice.h"
#include "IRadiance/Framework/Renderer/API/RenderCommand.h"
#include "IRadiance/Framework/Renderer/Render.h"

#include "IRadiance/Framework/Renderer/MeshRender.h"
#include "IRadiance/Framework/Renderer/API/Texture2D.h"
#include "IRadiance/Framework/Renderer/API/Shader.h"

#include "IRadiance/Framework/Prefab/Prefab.h"

namespace IRadiance
{
	BaseLayer::BaseLayer(Application* _application)
		: Layer(_application)
	{
		RenderDevice* renderDevice = Locator::Get<RenderDevice>();

		std::string vertexShader = ReadFile("res/shaders/Quad.vs");
		std::string fragmentShader = ReadFile("res/shaders/Quad.fs");
		Shader* shader = renderDevice->CreateShader(vertexShader, fragmentShader);

		m_QuadRender = new MeshRender(CreateQuad(), shader);
	}

	BaseLayer::~BaseLayer()
	{
		delete m_QuadRender;
		delete m_Texture;
	}

	void BaseLayer::Render()
	{
		RenderCommand::SetClearColor({ 1.0f, 1.0f, 0.0f, 1.0f });

		Render::Begin();
		{
			RenderCommand::Clear();

			int slot = 0;
			m_Texture->Update();
			m_Texture->Bind(slot);
			m_QuadRender->GetShader()->SetUniformInt("u_Texture", slot);

			Render::Submit(m_QuadRender);
		}
		Render::End();
	}

}