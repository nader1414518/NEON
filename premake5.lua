workspace "Neon"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "NEON/vendor/GLFW/include"
IncludeDir["Glad"] = "NEON/vendor/Glad/include"
IncludeDir["ImGui"] = "NEON/vendor/imgui"
IncludeDir["glm"] = "NEON/vendor/glm"

include "NEON/vendor/GLFW"
include "NEON/vendor/Glad"
include "NEON/vendor/imgui"
-- include "NEON/vendor/glm"

project "Neon"
    location "Neon"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    -- pchheader "NEON_PCH.h"
    -- pchsource "Neon/src/NEON_PCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links 
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "IMGUI_API=__declspec(dllexport)",
            "NEON_PLATFORM_WINDOWS",
            "NEON_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
            -- "_CRT_SECURE_NO_WARNINGS"
        }

        -- postbuildcommands
        -- {
        --     ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        -- }

    filter "configurations:Debug"
        defines "NEON_DEBUG"
        -- buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "NEON_RELEASE"
        -- buildoptions "/MD"
        optimize "on"

    -- filter "configurations:Dist"
    --     defines "NEON_DIST"
    --     buildoptions "/MD"
    --     optimize "on"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Neon/src",
        "NEON/vendor/imgui",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Neon"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "IMGUI_API=__declspec(dllimport)",
            "NEON_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "NEON_DEBUG"
        -- buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "NEON_RELEASE"
        -- buildoptions "/MD"
        optimize "on"

    -- filter "configurations:Dist"
    --     defines "NEON_DIST"
    --     buildoptions "/MD"
    --     optimize "on"