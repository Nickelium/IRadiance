#include "pch.h"
#include "ImageBuffer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace IRadiance
{
	ImageBuffer::ImageBuffer(int _width, int _height)
		:m_Width(_width), m_Height(_height)
	{
		m_Buffer = new RGBA[m_Width * m_Height];
		Clear();
	}

	ImageBuffer::~ImageBuffer()
	{
		delete m_Buffer;
	}

	void ImageBuffer::Write(const std::string& _file)
	{
		std::string file(_file);
		std::string ext(".jpg");

		int i = 0;
		while (true)
		{
			{
				std::ifstream stream(file + ext);
				if(!stream.good())
					break;
			}
			file = _file + std::string("_") + std::to_string(i);
			++i;
		}
		stbi_flip_vertically_on_write(1);
		stbi_write_jpg((file + ext).c_str(), m_Width, m_Height, 4, m_Buffer, 100);
	}

	void ImageBuffer::Clear()
	{
		for (RGBA* ptr = m_Buffer,
			*end = m_Buffer + m_Width * m_Height;
			ptr < end;
			++ptr)
			*ptr = RGBA{ 0, 0, 0, 255 };
	}

	ImageBuffer::ProxyRow ImageBuffer::operator[](unsigned int row)
	{
		return ProxyRow(*this, row);
	}

	RGBA& ImageBuffer::ProxyRow::operator[](unsigned int col)
	{
		return m_FrameBuffer.m_Buffer[m_Row * m_FrameBuffer.m_Width + col];
	}

	ImageBuffer::ProxyRow::ProxyRow(ImageBuffer& parent, unsigned int row)
		: m_FrameBuffer(parent), m_Row(row)
	{
	}

}