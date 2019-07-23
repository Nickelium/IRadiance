#include "pch.h"
#include "GLRenderDevice.h"

#include "GLVertexArray.h"
#include "GLBuffer.h"
#include "GLShader.h"
#include "GLTexture2D.h"

#include "IRadiance/Framework/Renderer/API/RenderCommand.h"
#include "GLRenderAPI.h"

namespace IRadiance
{
	std::unique_ptr<RenderAPI> RenderCommand::s_RenderAPI = 
		std::make_unique<GLRenderAPI>();
	//RenderAPI* RenderCommand::s_RenderAPI = new GLRenderAPI;
		
	VertexArray* GLRenderDevice::CreateVertexArray() const
	{
		return new GLVertexArray;
	}

	VertexBuffer* GLRenderDevice::CreateVertexBuffer(std::vector<float> _vertices) const
	{
		return new GLVertexBuffer(_vertices);
	}

	IndexBuffer* GLRenderDevice::CreateIndexBuffer(std::vector<uint32_t> _indices) const
	{
		return new GLIndexBuffer(_indices);
	}

	Shader* GLRenderDevice::CreateShader(const std::string& _vertexSource, const std::string& _fragmentSource) const
	{
		return new GLShader(_vertexSource, _fragmentSource);
	}

	Texture2D* GLRenderDevice::CreateTexture2D(const std::string& _filePath) const
	{
		return new GLTexture2D(_filePath);
	}

	Texture2D* GLRenderDevice::CreateTexture2D(int _width, int _height) const
	{
		return new GLAccessibleTexture2D(_width, _height);
	}

}