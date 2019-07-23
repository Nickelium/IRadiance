#include "pch.h"
#include "GLBuffer.h"

#include <glad/glad.h>

namespace IRadiance
{
	#pragma region VERTEXBUFFER
	GLVertexBuffer::GLVertexBuffer(std::vector<float> _vertices)
	{
		//Alternative but cause crashes due to OpenGL 4.5 or so ?
		//glCreateBuffers(1, &m_ID);
		glGenBuffers(1, &m_Handle);
		Bind();
		uint32_t nbBytes = sizeof(float) * (uint32_t)_vertices.size();
		glBufferData(GL_ARRAY_BUFFER, nbBytes, _vertices.data(), GL_STATIC_DRAW);
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		glDeleteBuffers(1, &m_Handle);
	}

	void GLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
	}

	void GLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	#pragma endregion

	#pragma  region INDEXBUFFER
	GLIndexBuffer::GLIndexBuffer(std::vector<uint32_t> _indices)
		: m_Count((uint32_t)_indices.size())
	{
		glGenBuffers(1, &m_Handle);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), _indices.data(), GL_STATIC_DRAW);
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glDeleteBuffers(1, &m_Handle);
	}

	void GLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
	}

	void GLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	#pragma endregion
}