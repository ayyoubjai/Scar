workspace "Scar"
	
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release"
	}

outputdir="%{cfg.buildcfg}"

externals={}
externals["sdl2"]="vendor/SDL2"
externals["spdlog"]="vendor/spdlog"
externals["glad"]="vendor/glad"
externals["glm"]="vendor/glm"
include "vendor/glad"

project "Scar"
	location "Scar"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/include/**.cpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/**.natvis"
	}
	
	includedirs
	{
		"%{prj.name}/include",
		"%{prj.name}/include/Scar",
		"%{externals.sdl2}/include",
		"%{externals.spdlog}/include",
		"%{externals.glad}/include",
		"%{externals.glm}/include"
	}

	defines
	{
		"GLFW_INCLUDE_NONE"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"SC_PLATFORM_WINDOWS",
			"SC_BUILD_DLL"
		}

		libdirs
		{
			"%{externals.sdl2}/lib",
			"%{externals.sdl2}/bin/" ..outputdir.."/%{prj.name}"

		}

		links
		{
			"SDL2",
			"glad"

		}

		postbuildcommands 
		{
			("{COPY} ../bin/" .. outputdir .. "/%{prj.name}/Scar.dll ../bin/" .. outputdir .. "/ScarEditor" ),
			("{COPY} ../%{externals.sdl2}/lib/SDL2.dll ../bin/" .. outputdir .. "/ScarEditor"),
			("{COPY} ../bin/" .. outputdir .. "/%{prj.name}/Scar.dll ../bin/" .. outputdir .. "/Pong" ),
			("{COPY} ../%{externals.sdl2}/lib/SDL2.dll ../bin/" .. outputdir .. "/Pong")
		}



	
	filter "system:linux"
		defines
		{
			"SC_PLATFORM_LINUX",
			"SC_BUILD_DLL"
		}

		links
		{
			"SDL2",
			"glad",
			"dl"

		}

	filter "configurations:Debug"
		defines
		{
			"SC_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		defines
		{
			"SC_RELEASE"
		}
		runtime "Release"
		optimize "On"


project "ScarEditor"
	location "ScarEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Scar/include",
		"Scar/include/Scar",
		"%{externals.spdlog}/include",
		"%{externals.glm}/include"


	}

	links
	{
		"Scar"
	}
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"SC_PLATFORM_WINDOWS",
		}

	filter "system:LINUX"
		defines
		{
			"SC_PLATFORM_LINUX",

		}

	filter "configurations:Debug"
		defines
		{
			"SC_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		defines
		{
			"SC_RELEASE"
		}
		runtime "Release"
		optimize "On"


project "Pong"
	location "Pong"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Scar/include",
		"Scar/include/Scar",
		"%{prj.name}/src",
		"%{externals.spdlog}/include",
		"%{externals.glm}/include"


	}

	links
	{
		"Scar"
	}
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"SC_PLATFORM_WINDOWS",
		}

	filter "system:LINUX"
		defines
		{
			"SC_PLATFORM_LINUX",

		}

	filter "configurations:Debug"
		defines
		{
			"SC_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		defines
		{
			"SC_RELEASE"
		}
		runtime "Release"
		optimize "On"
