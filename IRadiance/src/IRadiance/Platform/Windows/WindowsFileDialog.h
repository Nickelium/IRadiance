#pragma once

#include "IRadiance/Framework/Core/FileDialog.h"

namespace IRadiance
{
	class WindowsFileDialog : public FileDialog
	{
	public:
		WindowsFileDialog(Window* _parentWindow) : m_ParentWindow(_parentWindow) {}
		virtual bool OpenFile(std::string& _ofile) const override;
	private:
		Window* m_ParentWindow;
	};
}
