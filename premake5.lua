workspace "Assec"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["glfw"] = "Assec/vendor/glfw/include"
	IncludeDir["glad"] = "Assec/vendor/glad/include"
	IncludeDir["imgui"] = "Assec/vendor/imgui"
	IncludeDir["glm"] = "Assec/vendor/glm"

	include "Assec/vendor/glfw"
	include "Assec/vendor/glad"
	include "Assec/vendor/imgui"

	project "Assec"
		location "Assec"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "acpch.h"
		pchsource "Assec/src/acpch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl"
		}

		defines
		{
			"_CRT_SECURE_NO_WARNINGS"
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.imgui}",
			"%{IncludeDir.glm}"
		}

		links
		{
			"glfw",
			"glad",
			"imgui",
			"opengl32.lib"
		}

		filter "system:windows"
			systemversion "latest"

			defines
			{
				"AC_PLATFORM_WINDOWS",
				"GLFW_INCLUDE_NONE"
			}

		filter "configurations:Debug"
			defines "AC_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "AC_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "AC_DIST"
			runtime "Release"
			optimize "on"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Assec/src",
			"%{wks.location}/Assec/vendor/spdlog/include",
			"%{IncludeDir.glm}",
			"%{IncludeDir.imgui}"
		}

		links
		{
			"Assec"
		}

		filter "system:windows"
			systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "DIST"
			runtime "Release"
			optimize "on"
