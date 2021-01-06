workspace "Assec"
	architecture "x64"
	startproject "Assec-Editor"

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
	IncludeDir["entt"] = "Assec/vendor/entt/single_include"
	IncludeDir["tinygltf"] = "Assec/vendor/tinygltf"
	IncludeDir["yaml_cpp"] = "Assec/vendor/yaml-cpp/include"
	IncludeDir["imnodes"] = "Assec/vendor/imnodes"
	IncludeDir["implot"] = "Assec/vendor/implot"
	IncludeDir["imguizmo"] = "Assec/vendor/imguizmo"



	group "Dependencies"
		include "Assec/vendor/glfw"
		include "Assec/vendor/glad"
		include "Assec/vendor/imgui"
		include "Assec/vendor/yaml-cpp"
		include "Assec/vendor/implot"
		include "Assec/vendor/imguizmo"
	group ""

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
			"C:/VulkanSDK/1.2.162.0/Include",
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{prj.name}/vendor/stb",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.imgui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.entt}",
			"%{IncludeDir.tinygltf}",
			"%{IncludeDir.yaml_cpp}"
		}

		libdirs
		{
			"C:/VulkanSDK/1.2.162.0/Lib"
		}

		links
		{
			"glfw",
			"glad",
			"imgui",
			"yaml-cpp",
			"opengl32.lib",
			"vulkan-1"
		}

		filter "system:windows"
			systemversion "latest"

			defines
			{
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
			"%{wks.location}/Assec/vendor/stb",
			"%{IncludeDir.glm}",
			"%{IncludeDir.entt}"
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

	project "Assec-Editor"
			location "Assec-Editor"
			kind "ConsoleApp"
			language "C++"
			cppdialect "C++17"
			staticruntime "on"

			targetdir ("bin/" .. outputdir .. "/%{prj.name}")
			objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

			files
			{
				"%{prj.name}/src/**.h",
				"%{prj.name}/src/**.cpp",
			}

			includedirs
			{
				"Assec/src",
				"%{wks.location}/Assec/vendor/spdlog/include",
				"%{wks.location}/Assec/vendor/stb",
				"%{IncludeDir.glm}",
				"%{IncludeDir.imgui}",
				"%{IncludeDir.imnodes}",
				"%{IncludeDir.implot}",
				"%{IncludeDir.entt}",
				"%{IncludeDir.imguizmo}"
			}

			links
			{
				"Assec",
				"Implot",
				"ImGuizmo"
			}

			filter "system:windows"
				systemversion "latest"

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
