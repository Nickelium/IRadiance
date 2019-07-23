#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Singleton.h"

namespace IRadiance
{
	class Logger : public Singleton<Logger>
	{
	public:
		Logger();
		inline std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{ return m_CoreLogger; }
		inline std::shared_ptr<spdlog::logger>& GetClientLogger() 
		{ return m_ClientLogger; } 
	private:
		void Init();
		std::shared_ptr<spdlog::logger> m_CoreLogger;
		std::shared_ptr<spdlog::logger> m_ClientLogger;
	};
}

#if defined(DEBUG) || defined(_DEBUG)
// Core log macros
#define IRAD_CORE_TRACE(...)    ::IRadiance::Logger::GetInstance().GetCoreLogger()->trace(__VA_ARGS__)
#define IRAD_CORE_INFO(...)     ::IRadiance::Logger::GetInstance().GetCoreLogger()->info(__VA_ARGS__)
#define IRAD_CORE_WARN(...)     ::IRadiance::Logger::GetInstance().GetCoreLogger()->warn(__VA_ARGS__)
#define IRAD_CORE_ERROR(...)    ::IRadiance::Logger::GetInstance().GetCoreLogger()->error(__VA_ARGS__)
#define IRAD_CORE_FATAL(...)    ::IRadiance::Logger::GetInstance().GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define IRAD_TRACE(...)		 ::IRadiance::Logger::GetInstance().GetClientLogger()->trace(__VA_ARGS__)
#define IRAD_INFO(...)		 ::IRadiance::Logger::GetInstance().GetClientLogger()->info(__VA_ARGS__)
#define IRAD_WARN(...)		 ::IRadiance::Logger::GetInstance().GetClientLogger()->warn(__VA_ARGS__)
#define IRAD_ERROR(...)		 ::IRadiance::Logger::GetInstance().GetClientLogger()->error(__VA_ARGS__)
#define IRAD_FATAL(...)		 ::IRadiance::Logger::GetInstance().GetClientLogger()->critical(__VA_ARGS__) 

#else

#define IRAD_CORE_TRACE(...)
#define IRAD_CORE_INFO(...)
#define IRAD_CORE_WARN(...)
#define IRAD_CORE_ERROR(...)
#define IRAD_CORE_FATAL(...)

// Client log macros
#define IRAD_TRACE(...)	
#define IRAD_INFO(...)
#define IRAD_WARN(...)	
#define IRAD_ERROR(...)	
#define IRAD_FATAL(...)	

#endif