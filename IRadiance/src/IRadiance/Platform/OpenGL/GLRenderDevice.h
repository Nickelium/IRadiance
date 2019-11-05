#pragma once

#include "IRadiance/Framework/Renderer/API/RenderDevice.h"

namespace IRadiance
{
	class GLRenderDevice : public RenderDevice
	{
	public:
		virtual ~GLRenderDevice() = default;

		virtual VertexArray* CreateVertexArray() const override;
		virtual VertexBuffer* CreateVertexBuffer(std::vector<float> _vertices) const override;
		virtual IndexBuffer* CreateIndexBuffer(std::vector<uint32_t> _indices) const override;
		virtual Shader* CreateShader(const std::string& _vertexSource, const std::string& _fragmentSource) const override;
		virtual Texture2D* CreateTexture2D(const std::string& _filePath) const override;
		virtual Texture2D* CreateWritableTexture2D(int _width, int _height) const override;
		virtual Texture2D* CreateWritableTexture2D(const std::string& _filePath) const override;

	};
}
