#pragma once
#if defined SC_STATIC
	#define SCAR_API

#elif defined SC_PLATFORM_WINDOWS

	#if defined SC_BUILD_DLL
		#define SCAR_API __declspec(dllexport)
	#else
		#define SCAR_API __declspec(dllimport)
	#endif

#elif defined SC_PLATFORM_LINUX
	#if defined SC_BUILD_DLL
		#define SCAR_API __attribute__((visibility("default")))
	#else
		#define SCAR_API
	#endif
#else
	#error "Not supported platform"
#endif
