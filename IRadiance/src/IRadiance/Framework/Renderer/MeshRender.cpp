#include "pch.h"
#include "MeshRender.h"

#include "API/VertexArray.h"
#include "API/Shader.h"
#include "Mesh.h"

#include "API/RenderDevice.h"

namespace IRadiance
{
	
	MeshRender::MeshRender(Mesh* _mesh, Shader* _shader)
		: m_Mesh(_mesh), m_Shader(_shader)
	{
		BuildVertexArray();
	}

	MeshRender::~MeshRender()
	{
		delete m_VertexArray;
		delete m_Mesh;
		delete m_Shader;
	}

	void MeshRender::Bind()
	{
		m_VertexArray->Bind();
		m_Shader->Bind();
	}

	void MeshRender::UnBind()
	{
		m_VertexArray->UnBind();
		m_Shader->UnBind();
	}

	void MeshRender::BuildVertexArray()
	{
		//TODO pack/tight
		std::vector<float> vertices;

		std::vector<glm::vec3> positions = m_Mesh->GetPositions();
		std::vector<glm::vec2> texCoords = m_Mesh->GetTexCoords();
		std::vector<uint32_t> indices = m_Mesh->GetIndices();
		int nbVertices = m_Mesh->GetNbVertices();
		for (int i = 0; i < nbVertices; ++i)
		{
			vertices.push_back(positions[i].x);
			vertices.push_back(positions[i].y);
			vertices.push_back(positions[i].z);
			vertices.push_back(texCoords[i].x);
			vertices.push_back(texCoords[i].y);
		}

		auto rd = Locator::Get<RenderDevice>();
		VertexArray* vertexArray = rd->CreateVertexArray();
		VertexBuffer* vertexBuffer = rd->CreateVertexBuffer(vertices);
		BufferLayout layout =
		{
			{DataType::Float3, "a_Position"},
			{DataType::Float2, "a_TexCoords"}
		};
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		IndexBuffer* indexBuffer = rd->CreateIndexBuffer(indices);
		vertexArray->SetIndexBuffer(indexBuffer);

		m_VertexArray = vertexArray;
	}

}