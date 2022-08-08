#include "managers/LogManager.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <vector>

namespace Scar::Managers {
	std::shared_ptr<spdlog::logger> LogManager::s_CoreLogger = nullptr;

	void LogManager::Initialize() {
		spdlog::set_pattern("%^[ %Y-%m-%d %H:%M:%S.%e ] %n %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("SCAR");
		s_CoreLogger->set_level(spdlog::level::trace);
	}

	void LogManager::ShutDown() {
		spdlog::shutdown();
	}
}