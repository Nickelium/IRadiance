#include "pch.h"
#include "ImageBuffer.h"

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