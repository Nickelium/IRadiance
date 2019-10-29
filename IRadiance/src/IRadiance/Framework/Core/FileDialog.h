#pragma once

#include "IRadiance/Framework/Core/Locator.h"

namespace IRadiance
{
	class Window;
	class FileDialog : public Service
	{
	public:
		virtual bool OpenFile(std::string& _ofile) const = 0;

		static FileDialog* Create(Window* _window);

		SERVICE_CLASS("FileDialog")
	};
}
