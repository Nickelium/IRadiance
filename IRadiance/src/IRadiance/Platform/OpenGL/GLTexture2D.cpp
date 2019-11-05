#include "pch.h"
#include "GLTexture2D.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "IRadiance/Framework/Renderer/ImageBuffer.h"

namespace IRadiance
{
	GLTexture2D::GLTexture2D(const std::string& _filePath)
		:m_Handle(0), m_Width(0), m_Height(0), m_BPP(0),
		m_Buffer(nullptr), m_FilePath(_filePath)
	{
		stbi_set_flip_vertically_on_load(1);

		m_Buffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		IRAD_CORE_ASSERT(m_Buffer != nullptr, "Can't find provided texture: {0}", m_FilePath);

		glGenTextures(1, &m_Handle);
		glBindTexture(GL_TEXTURE_2D, m_Handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_Buffer)
			stbi_image_free(m_Buffer);
	}

	GLTexture2D::~GLTexture2D()
	{
		glDeleteTextures(1, &m_Handle);
	}

	void GLTexture2D::Bind(unsigned int _slot /*= 0*/)
	{
		glActiveTexture(GL_TEXTURE0 + _slot);
		glBindTexture(GL_TEXTURE_2D, m_Handle);
	}

	void GLTexture2D::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLAccessibleTexture2D::GLAccessibleTexture2D(int _width, int _height)
		:m_Handle(0), m_Width(_width), m_Height(_height), m_BPP(4),
		m_ImageBuffer(new ImageBuffer(m_Width, m_Height))
	{
		glGenTextures(1, &m_Handle);
		glBindTexture(GL_TEXTURE_2D, m_Handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImageBuffer->GetBuffer());
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLAccessibleTexture2D::GLAccessibleTexture2D(const std::string& _fileName)
		:m_Handle(0), m_Width(0), m_Height(0), m_BPP(4),
		m_ImageBuffer(nullptr)
	{
		stbi_set_flip_vertically_on_load(1);
		int containedBPP;
		unsigned char* buffer = stbi_load(_fileName.c_str(), &m_Width, &m_Height, &containedBPP, m_BPP);
		IRAD_CORE_ASSERT(buffer != nullptr, "Can't find provided texture: {0}", _fileName);

		m_ImageBuffer = new ImageBuffer(m_Width, m_Height);
		m_ImageBuffer->Fill(buffer, m_Width * m_Height * m_BPP);

		glGenTextures(1, &m_Handle);
		glBindTexture(GL_TEXTURE_2D, m_Handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImageBuffer->GetBuffer());
		glBindTexture(GL_TEXTURE_2D, 0);

		if (buffer)
			stbi_image_free(buffer);
	}
	
	GLAccessibleTexture2D::~GLAccessibleTexture2D()
	{
		glDeleteTextures(1, &m_Handle);
		delete m_ImageBuffer;
	}


	void GLAccessibleTexture2D::Bind(unsigned int _slot /*= 0*/)
	{
		glActiveTexture(GL_TEXTURE0 + _slot);
		glBindTexture(GL_TEXTURE_2D, m_Handle);
	}

	void GLAccessibleTexture2D::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	ImageBuffer* GLAccessibleTexture2D::GetImageBuffer() const
	{
		return m_ImageBuffer;
	}

	void GLAccessibleTexture2D::Update()
	{
		/*for (int i = 0; i < m_Width * m_Height * m_BPP; i += m_BPP)
		{
			m_Buffer[i + 0] = (m_Buffer[i + 0] + 1) % 255;
			m_Buffer[i + 1] = 127;
			m_Buffer[i + 2] = 127;
			m_Buffer[i + 3] = 255;
		}*/
		int prevTexture;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &prevTexture);
		glBindTexture(GL_TEXTURE_2D, m_Handle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImageBuffer->GetBuffer());
		glBindTexture(GL_TEXTURE_2D, prevTexture);
		//glBindTexture(GL_TEXTURE_2D, 0); //CAUSE PROBLEM!!!!!
	}

}