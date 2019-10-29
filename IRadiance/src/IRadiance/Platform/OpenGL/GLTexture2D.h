#pragma once

#include "IRadiance/Framework/Renderer/API/Texture2D.h"

namespace IRadiance
{
	class GLTexture2D : public Texture2D
	{
	public:
		GLTexture2D(const std::string& _filePath);
		virtual ~GLTexture2D();

		virtual void Bind(unsigned int _slot = 0) override;
		virtual void UnBind() override;

		inline virtual int GetWidth() const override { return m_Width; }
		inline virtual int GetHeight() const override { return m_Height; }

		/**
		 * Not used, can be used but not performant to store actual imagebuffer
		 */
		inline virtual void Update() override {}
		inline virtual ImageBuffer* GetImageBuffer() const override { return nullptr; }

		Handle m_Handle;
	private:
		std::string m_FilePath;
		unsigned char* m_Buffer;
		int m_Width, m_Height, m_BPP;
	};
	
	class ImageBuffer;
	class GLAccessibleTexture2D : public Texture2D
	{
	public:
		GLAccessibleTexture2D(int _width, int _height);
		GLAccessibleTexture2D(const std::string& _fileName);
		virtual ~GLAccessibleTexture2D();

		virtual void Bind(unsigned int _slot = 0) override;
		virtual void UnBind() override;

		inline virtual int GetWidth() const override { return m_Width; }
		inline virtual int GetHeight() const override { return m_Height; }

		virtual ImageBuffer* GetImageBuffer() const override;

		virtual void Update();

		Handle m_Handle;
	private:
		int m_Width, m_Height, m_BPP;
		ImageBuffer* m_ImageBuffer;
	};
}
