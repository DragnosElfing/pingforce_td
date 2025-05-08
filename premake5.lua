local leak_file = "leak.txt"

workspace "PingForce_TD"
    startproject "pingforce"
    configurations {
        "Release",
        "Debug"
    }

    language "C++"
    cppdialect "c++17"
    toolset "clang"
    targetdir "./bin/%{prj.name}_%{cfg.buildcfg}"
    objdir "./bin-int"

project "pingforce"
    kind "WindowedApp"
    targetname "pingforce"

    files {
        "src/utils/**.cpp",
        "src/scenes/**.cpp",
        "src/gui/*.cpp",
        "src/game/*.cpp",
        "src/*.cpp"
    }

    includedirs {
        "include"
    }

    externalincludedirs {
        "external/sfml/include"
    }

    libdirs {
        "external/**/lib"
    }

    filter {"system:linux", "action:gmake"}
        pchheader "all.hpp"

        links {
            "sfml-audio-s",
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
            "pthread",
            "FLAC",
            "vorbis",
            "vorbisenc",
            "vorbisfile",
            "ogg"
        }

        filter "configurations:Debug"
            symbols "On"
            defines {
                "_PFTD_DEBUG"
            }

            buildoptions {
                "-pedantic",
                "-gdwarf-4"
            }
            
            flags {
                "FatalWarnings"
            }
            
            warnings "Extra" -- -Wall -Wextra
            externalwarnings "Off"

            disablewarnings {
                "unused-lambda-capture",

                -- GNU extensions
                "gnu-anonymous-struct",
                "nested-anon-types"
            }
            
        filter "configurations:Release"
            optimize "On"
            
            warnings "Off"
            externalwarnings "Off"


project "pingforce_test"
    kind "ConsoleApp"
    targetname "test"

    files {
        "test/tests.cpp",
        "src/utils/parsers/*.cpp"
    }

    includedirs {
        "test/include"
    }

    externalincludedirs {
        "include",
        "." -- memtrace.h és gtest_lite.h miatt, amit a JPorta szúr be
    }

    defines {
        "_PFTD_TEST"
    }

    postbuildcommands {
        "valgrind --tool=memcheck --track-origins=yes --leak-check=full %{cfg.buildtarget.name} &> %{prj.location}/%{leak_file}"
    }

    filter {"system:linux", "action:gmake"}
        symbols "On"
        optimize "Off"
        warnings "Extra"
        externalwarnings "Off"
