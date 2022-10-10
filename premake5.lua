workspace "Neon"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Neon"
    location "Neon"
    kind "SharedLib"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    -- pchheader "NEON_PCH.h"
    -- pchsource "Neon/src/NEON_PCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "NEON_PLATFORM_WINDOWS",
            "NEON_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "NEON_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NEON_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "NEON_DIST"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Neon/vendor/spdlog/include",
        "Neon/src"
    }

    links
    {
        "Neon"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "NEON_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "NEON_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NEON_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "NEON_DIST"
        optimize "On"
