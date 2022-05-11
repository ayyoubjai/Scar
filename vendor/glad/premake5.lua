project "glad"
kind "StaticLib"
language "C"
staticruntime "On"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-obj/" .. outputdir .. "/%{prj.name}")

files
{
	"include/**.h",
	"src/**.c"
}

includedirs
{
	"include"
}

filter "system:windows"
	systemversion "latest"

filter "configurations:Debug"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	runtime "Release"
	optimize "On"