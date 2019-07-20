#include "pch.h"
#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace IRadiance
{
	Logger::Logger()
	{
		Init();
	}

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		m_ClientLogger = spdlog::stdout_color_mt("CLI");
		m_ClientLogger->set_level(spdlog::level::trace);
		m_CoreLogger = spdlog::stdout_color_mt("COR");
		m_CoreLogger->set_level(spdlog::level::trace);
	}

}