#pragma once
#include "IRadiance/Framework/Renderer/API/VertexArray.h"

namespace IRadiance
{
	class GLVertexArray : public VertexArray
	{
	public:
		GLVertexArray();
		virtual ~GLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(VertexBuffer* _vertexBuffer) override;
		virtual void SetIndexBuffer(IndexBuffer* _indexBuffer) override;

		virtual const VertexBuffers& GetVertexBuffers() const override;
		virtual const IndexBuffer* GetIndexBuffer() const override;

	private:
		Handle m_Handle;
		VertexBuffers m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;
	};
}
