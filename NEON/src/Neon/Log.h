#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Neon {
	class NEON_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
			return s_CoreLogger;
		};

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
			return s_ClientLogger;
		};

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
};

// Core log macros
#define NeonCoreLogError(...)	::Neon::Log::GetCoreLogger()->error(__VA_ARGS__);
#define NeonCoreLogWarning(...)	::Neon::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define NeonCoreLogInfo(...)	::Neon::Log::GetCoreLogger()->info(__VA_ARGS__);
#define NeonCoreLogDebug(...)	::Neon::Log::GetCoreLogger()->debug(__VA_ARGS__);
#define NeonCoreLogTrace(...)	::Neon::Log::GetCoreLogger()->trace(__VA_ARGS__);


// Client log macros
#define NeonLogError(...)	::Neon::Log::GetClientLogger()->error(__VA_ARGS__);
#define NeonLogWarning(...)	::Neon::Log::GetClientLogger()->warn(__VA_ARGS__);
#define NeonLogInfo(...)	::Neon::Log::GetClientLogger()->info(__VA_ARGS__);
#define NeonLogDebug(...)	::Neon::Log::GetClientLogger()->debug(__VA_ARGS__);
#define NeonLogTrace(...)	::Neon::Log::GetClientLogger()->trace(__VA_ARGS__);