#include "managers/LogManager.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <vector>

namespace Scar::Managers {
	std::shared_ptr<spdlog::logger> LogManager::s_CoreLogger = nullptr;
	std::shared_ptr<spdlog::logger> LogManager::s_ClientLogger = nullptr;

	void LogManager::Initialize() {
		/*
		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_pattern("%^[ %Y-%m-%d %H:%M:%S.%e ] %n %v%$");////

		std::vector<spdlog::sink_ptr> sinks{ consoleSink };
		auto logger = std::make_shared<spdlog::logger>("ScarLogger",sinks.begin(),sinks.end());
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(logger);
		*/

		spdlog::set_pattern("%^[ %Y-%m-%d %H:%M:%S.%e ] %n %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("SCAR");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);


	}

	void LogManager::ShutDown() {
		spdlog::shutdown();
	}
}