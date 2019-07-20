#pragma once

#include "Buffer.h"

namespace IRadiance
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(VertexBuffer* _vertexBuffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* _indexBuffer) = 0;

		using VertexBuffers = std::vector<VertexBuffer*>;

		virtual const VertexBuffers& GetVertexBuffers() const = 0;
		virtual const IndexBuffer* GetIndexBuffer() const = 0;

	};
}
