workspace "graphite"
  configurations { "Debug", "Release" }
  architecture "x86_64"

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "grc"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"

  targetdir ("bin/" .. outdir)
  targetdir ("bin/int/" .. outdir)
  
  files {
    "%{wks.location}/src/**.h",
    "%{wks.location}/src/**.cpp",
  }

  includedirs {
    "%{wks.location}/libs/spdlog/include"
  }

  filter "system:windows"
    systemversion "latest"

  filter "configurations:Debug"
		defines "GRC_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "GRC_RELEASE"
		optimize "On"