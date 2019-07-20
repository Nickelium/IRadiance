#pragma once

#include <vector>

namespace IRadiance
{
	enum class DataType : uint8_t
	{
		Float = 0, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool,
		None
	};

	struct DataTypeInfo
	{
		DataType type;
		DataTypeInfo(DataType _type) : type(_type) {}
		uint32_t GetNbBytes() const;
		uint32_t GetComponentCount() const;
	};

	struct BufferElement
	{
		DataTypeInfo type;
		std::string name;
		uint32_t offset;
		bool normalized;

		BufferElement(DataType _type, const std::string& _name, bool _normalized = false) :
			type(_type), name(_name), offset(0), normalized(_normalized) {}
	};

	class BufferLayout
	{
	public:
		using BufferElements = std::vector<BufferElement>;
		using BufferIterator = BufferElements::iterator;
		using BufferCIterator = BufferElements::const_iterator;

		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& _elements) :
			m_Elements(_elements) 
		{ ComputeOffsetAndStride();}
		inline const BufferElements& GetElements() const { return m_Elements; };
		inline uint32_t GetStride() const { return m_Stride; }

		inline BufferCIterator begin() const { return m_Elements.cbegin(); }
		inline BufferCIterator end() const { return m_Elements.cend(); }
		inline BufferIterator begin() { return m_Elements.begin(); }
		inline BufferIterator end() { return m_Elements.end(); }
	private:
		void ComputeOffsetAndStride()
		{
			uint32_t offset = 0u;
			for (auto& elem : m_Elements)
			{
				elem.offset = offset;
				offset += elem.type.GetNbBytes();
			}
			m_Stride = offset;
		}

		BufferElements m_Elements;
		uint32_t m_Stride = 0;
			
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(const BufferLayout& _layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
	};

	class IndexBuffer
	{
	public:	
		virtual ~IndexBuffer() = default;
	
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;
	};
}
