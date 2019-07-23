#pragma once

#include "IRadiance/Framework/Renderer/API/Buffer.h"

namespace IRadiance
{

	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(std::vector<float> _vertices);
		virtual ~GLVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		inline virtual void SetLayout(const BufferLayout& _layout) override { m_Layout = _layout; }
		inline virtual const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		Handle m_Handle;

		BufferLayout m_Layout;
	};

	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(std::vector<uint32_t> _indices);
		virtual ~GLIndexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		inline virtual uint32_t GetCount() const override { return m_Count; }
	private:
		Handle m_Handle;

		uint32_t m_Count;
	};
}
