#pragma once

namespace IRadiance
{
	struct RGBA
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};

	class ImageBuffer
	{
	public:
		ImageBuffer(int _width, int _height);
		~ImageBuffer();

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		inline RGBA* GetBuffer() const { return m_Buffer; }

		void Write(const std::string& _file);

		void Clear();

		class ProxyRow;
		class ProxyRowConst;

		ProxyRow operator[](unsigned int row);

		class ProxyRow
		{
			friend class ImageBuffer;
		public:
			RGBA& operator[](unsigned int col);
		private:
			ProxyRow(ImageBuffer& _frameBuffer, unsigned int _row);
			unsigned int m_Row;
			ImageBuffer& m_FrameBuffer;
		};
		friend class ProxyRow;

	private:
		int m_Width;
		int m_Height;
		//FORMAT RGBA
		RGBA* m_Buffer;
	};
}