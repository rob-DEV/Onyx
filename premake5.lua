workspace "Onyx"
    architecture "x64"

    configurations { 
        "Debug", 
        "Release" 
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

project "Onyx"
    location "Onyx"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",

        "%{prj.name}/vendor/glm/**.hpp",
        "%{prj.name}/vendor/glad/**.cpp",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/tinyxml2/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/glm",
        "%{prj.name}/vendor/glfw3",
        "%{prj.name}/vendor/glad/include",
        "%{prj.name}/vendor/stb_image",
        "%{prj.name}/vendor/vulkan",
        "%{prj.name}/vendor/openal",
        "%{prj.name}/vendor/assimp",
        "%{prj.name}/vendor/entt/include",
        "%{prj.name}/vendor/tinyxml2"
    }

    libdirs { 
        "%{prj.name}/vendor/glfw3/lib",
        "%{prj.name}/vendor/vulkan/lib",
        "%{prj.name}/vendor/openal/lib",
        "%{prj.name}/vendor/assimp/lib",
    }

    links {
        "glfw3.lib",
        "glfw3dll.lib",
        "vulkan-1.lib",
        "OpenAL32.lib",
        "assimp-vc142-mt.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"

        defines {
            "_ONYX_BUILD_TARGET_WINDOWS_",
            "_ONYX_BUILD_DLL_"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Onyx-Sandbox"),
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Onyx-CLR"),
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Onyx-Editor-NET")
        }

    filter "configurations:Debug"
        defines "_ONYX_DEBUG_"
        symbols "On"

    filter "configurations:Release"
        optimize "On"


project "Onyx-CLR"
    location "Onyx-CLR"
    kind "SharedLib"
    language "C++"
    clr "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files  {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Onyx/src",
        "Onyx/vendor/glm",
        "Onyx/vendor/entt/include",
        "%{prj.name}/src"
    }

    links {
        "Onyx"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

    filter "configurations:Debug"
        defines "_ONYX_DEBUG_"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

project "Onyx-Editor-NET"
    location "Onyx-Editor-NET"
    namespace ("Onyx_Editor_NET")
    kind "WindowedApp"
    language "C#"
    clr "Unsafe"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files  {
        "%{prj.name}/src/**.cs",
        "%{prj.name}/src/**.xaml",
        "%{prj.name}/src/**.config",
        "%{prj.name}/src/**.jpg"
    }

    links {
        "Onyx-CLR",
        "System",
        "System.Data",
        "System.Drawing",
        "System.Windows.Forms",
        "System.Xml",
        "Microsoft.CSharp",
        "System.Core",
        "System.Xml.Linq",
        "System.Data.DataSetExtensions",
        "System.Net.Http",
        "System.Xaml",
        "WindowsBase",
        "PresentationCore",
        "PresentationFramework"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

    filter "configurations:Debug"
        defines "_ONYX_DEBUG_"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

project "Onyx-Sandbox"
    location "Onyx-Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files  {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Onyx/src",
        "Onyx/vendor/glm",
        "Onyx/vendor/entt/include"
    }

    links {
        "Onyx"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines "_ONYX_DEBUG_"
        symbols "On"

    filter "configurations:Release"
        optimize "On"
