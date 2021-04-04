#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <memory>

namespace Xeno
{
    class XENO_API Logger : public NonCopyable
    {
	public:
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return mCoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return mCoreLogger; }

	private:
		Logger();

		static std::shared_ptr<spdlog::logger> mCoreLogger;
		static std::shared_ptr<spdlog::logger> mClientLogger;

		friend class Application;
    };
}

// Core log macros
#define XN_CORE_TRACE(...)    ::Xeno::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define XN_CORE_INFO(...)     ::Xeno::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define XN_CORE_WARN(...)     ::Xeno::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define XN_CORE_ERROR(...)    ::Xeno::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define XN_CORE_CRITICAL(...) ::Xeno::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define XN_TRACE(...)         ::Xeno::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define XN_INFO(...)          ::Xeno::Logger::GetClientLogger()->info(__VA_ARGS__)
#define XN_WARN(...)          ::Xeno::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define XN_ERROR(...)         ::Xeno::Logger::GetClientLogger()->error(__VA_ARGS__)
#define XN_CRITICAL(...)      ::Xeno::Logger::GetClientLogger()->critical(__VA_ARGS__)