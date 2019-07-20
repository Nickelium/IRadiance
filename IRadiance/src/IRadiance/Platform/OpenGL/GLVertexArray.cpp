#include "pch.h"
#include "GLVertexArray.h"

#include <glad/glad.h>

namespace IRadiance
{
	static GLenum DataTypeToOpenGLBaseType(DataTypeInfo _type)
	{
		switch (_type.type)
		{
		case DataType::Float: return GL_FLOAT;
		case DataType::Float2: return GL_FLOAT;
		case DataType::Float3: return GL_FLOAT;
		case DataType::Float4: return GL_FLOAT;
		case DataType::Int: return GL_INT;
		case DataType::Int2: return GL_INT;
		case DataType::Int3: return GL_INT;
		case DataType::Int4: return GL_INT;
		case DataType::Mat3: return GL_FLOAT;
		case DataType::Mat4: return GL_FLOAT;
		case DataType::Bool: return GL_BOOL;
		}
		IRAD_CORE_ASSERT(false, "Invalid DataType");
		return 0;
	}

	GLVertexArray::GLVertexArray()
	{
		glGenVertexArrays(1, &m_Handle);
	}

	GLVertexArray::~GLVertexArray()
	{
		for (auto& vertexBuffer : m_VertexBuffers)
			delete vertexBuffer;
		delete m_IndexBuffer;
		glDeleteVertexArrays(1, &m_Handle);
	}

	void GLVertexArray::Bind() const
	{
		glBindVertexArray(m_Handle);
	}

	void GLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void GLVertexArray::AddVertexBuffer(VertexBuffer* _vertexBuffer)
	{
		IRAD_CORE_ASSERT(_vertexBuffer->GetLayout().GetElements().size() > 0,
			"Layout has no elements, VertexBuffer should first set Layout then add to VertexArray");

		Bind();
		_vertexBuffer->Bind();

		uint32_t index = 0;
		for (const auto& elem : _vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				elem.type.GetComponentCount(),
				DataTypeToOpenGLBaseType(elem.type),
				elem.normalized ? GL_TRUE : GL_FALSE, _vertexBuffer->GetLayout().GetStride(),
				(void*)(uintptr_t)(elem.offset));
			++index;
		}

		m_VertexBuffers.push_back(_vertexBuffer);
		UnBind();
	}

	void GLVertexArray::SetIndexBuffer(IndexBuffer* _indexBuffer)
	{
		m_IndexBuffer = _indexBuffer;
		Bind();
		m_IndexBuffer->Bind();
		UnBind();
	}

	const IRadiance::VertexArray::VertexBuffers& GLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const IRadiance::IndexBuffer* GLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

}