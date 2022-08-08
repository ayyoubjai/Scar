#pragma once
#include "managers/LogManager.h"


#if defined(SC_PLATFORM_WINDOWS)
#define SCAR_BREAK __debugbreak()
#elif defined(SC_PLATFORM_LINUX)
#define SCAR_BREAK __builtin_trap()
#endif
#if defined(SC_DEBUG)
#define SCAR_TRACE(...) Scar::Managers::LogManager::GetCoreLogger()->trace(__VA_ARGS__)//if( spdlog::get("ScarLogger") != nullptr ) {spdlog::get("ScarLogger")->trace(__VA_ARGS__);}
#define SCAR_DEBUG(...) Scar::Managers::LogManager::GetCoreLogger()->debug(__VA_ARGS__)//if( spdlog::get("ScarLogger") != nullptr ) {spdlog::get("ScarLogger")->debug(__VA_ARGS__);}
#define SCAR_INFO(...)  Scar::Managers::LogManager::GetCoreLogger()->info(__VA_ARGS__)//if( spdlog::get("ScarLogger") != nullptr ) {spdlog::get("ScarLogger")->info(__VA_ARGS__);}
#define SCAR_WARN(...)  Scar::Managers::LogManager::GetCoreLogger()->warn(__VA_ARGS__)//if( spdlog::get("ScarLogger") != nullptr ) {spdlog::get("ScarLogger")->warn(__VA_ARGS__);}
#define SCAR_ERROR(...) Scar::Managers::LogManager::GetCoreLogger()->error(__VA_ARGS__)//if( spdlog::get("ScarLogger") != nullptr ) {spdlog::get("ScarLogger")->error(__VA_ARGS__);}
#define SCAR_FATAL(...) Scar::Managers::LogManager::GetCoreLogger()->critical(__VA_ARGS__)//if( spdlog::get("ScarLogger") != nullptr ) {spdlog::get("ScarLogger")->critical(__VA_ARGS__);}
#define SCAR_ASSERT(x,msg) if((x)) {} else{ SCAR_FATAL("ASSERT {} {} \nFILE : {}\nLINE : {}",#x,msg,__FILE__,__LINE__); SCAR_BREAK;}
#elif defined(SC_RELEASE)
#define SCAR_TRACE(...) (void)0
#define SCAR_DEBUG(...) (void)0
#define SCAR_INFO(...) (void)0
#define SCAR_WARN(...) (void)0
#define SCAR_ERROR(...) (void)0
#define SCAR_FATAL(...) (void)0
#define SCAR_ASSERT(x,msg) (void)0
#endif


