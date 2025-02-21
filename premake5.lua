workspace "PingForce_TD"
    startproject "pingforce"
    configurations {
        "Release",
        "Debug"
    }

project "pingforce"
    kind "WindowedApp"
    language "C++"
    cppdialect "c++20"
    toolset "clang"
    targetdir "./bin/%{prj.name}_%{cfg.buildcfg}"
    targetname "pingforce"
    objdir "./bin-int"

    files {
        "src/utils/*.cpp",
        "src/objects/*.cpp",
        "src/main.cpp"
    }

    includedirs {
        "include",
        "." -- memtrace.h, gtest_lite.h miatt
    }

    externalincludedirs {
        "external/sfml/include"
    }

    libdirs {
        "external/**/lib"
    }

    
    filter {"system:linux", "action:gmake"}
        links {
            "sfml-window-s",
            "sfml-graphics-s",
            "sfml-system-s",
            "freetype",
            "X11",
            "Xrandr",
            "Xcursor",
            "Xi",
            "udev",
            "GL",
            "GLEW",
            "pthread"
        }

        buildoptions {
            "-pedantic",
            "-gdwarf-4"
        }


    filter "configurations:Debug"
        symbols "On"
        defines {
            "_DEBUG"
        }

        warnings "Everything"
        externalwarnings "Off"
        disablewarnings {
            -- "unused-parameter",
            -- "unused-macros",
            -- "newline-eof",
            -- "padded",
            -- "switch-enum",
            -- "gnu-zero-variadic-macro-arguments",
            -- "declaration-after-statement",
            "c++98-compat",
            "c++98-compat-pedantic"
        }

    filter "configurations:Release"
        optimize "On"

        warnings "Off"
        externalwarnings "Off"