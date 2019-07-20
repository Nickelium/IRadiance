#include "pch.h"
#include "Buffer.h"

#include "IRadiance/Platform/OpenGL/GLBuffer.h"
#include "IRadiance/Framework/Renderer/Render.h"

namespace IRadiance
{
	uint32_t DataTypeInfo::GetNbBytes() const
	{
		switch (type)
		{
		case IRadiance::DataType::Float:	 return 4 * 1;
		case IRadiance::DataType::Float2: return 4 * 2;
		case IRadiance::DataType::Float3: return 4 * 3;
		case IRadiance::DataType::Float4: return 4 * 4;
		case IRadiance::DataType::Int:	 return 4 * 1;
		case IRadiance::DataType::Int2:	 return 4 * 2;
		case IRadiance::DataType::Int3:	 return 4 * 3;
		case IRadiance::DataType::Int4:	 return 4 * 4;
		case IRadiance::DataType::Mat3:	 return 4 * 9;
		case IRadiance::DataType::Mat4:	 return 4 * 16;
		case IRadiance::DataType::Bool:	 return 1;
		}
		IRAD_CORE_ASSERT(false, "Invalid DataType");
		return 0u;
	}

	uint32_t DataTypeInfo::GetComponentCount() const
	{
		switch (type)
		{
		case IRadiance::DataType::Float:	 return 1;
		case IRadiance::DataType::Float2: return 2;
		case IRadiance::DataType::Float3: return 3;
		case IRadiance::DataType::Float4: return 4;
		case IRadiance::DataType::Int:	 return 1;
		case IRadiance::DataType::Int2:	 return 2;
		case IRadiance::DataType::Int3:	 return 3;
		case IRadiance::DataType::Int4:	 return 4;
		case IRadiance::DataType::Mat3:	 return 9;
		case IRadiance::DataType::Mat4:	 return 16;
		case IRadiance::DataType::Bool:	 return 1;
		}
		IRAD_CORE_ASSERT(false, "Invalid DataType");
		return 0u;
	}

}