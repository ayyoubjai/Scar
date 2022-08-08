#pragma once
#include <memory>
#include "core/core.h"
#include "spdlog/spdlog.h"
namespace Scar::Managers {

	class SCAR_API LogManager{
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		//static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		void Initialize();
		void ShutDown();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		//inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	};
}