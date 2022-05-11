#pragma once
#if defined SC_PLATFORM_WINDOWS

	#if defined SC_BUILD_DLL
		#define SCAR_API __declspec(dllexport)
	#else
		#define SCAR_API __declspec(dllimport)
	#endif

#elif defined SC_PLATFORM_LINUX
	#if defined SC_BUILD_DLL
		#define SCAR_API __declspec(dllexport)
	#else
		#define SCAR_API __declspec(dllimport)
	#endif
#else
	#error "Not supported platform"
#endif
