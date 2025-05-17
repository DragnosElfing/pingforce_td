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

        local libs = {
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

        filter "configurations:Release"
            links {
                libs
            }

            optimize "On"

            warnings "Off"
            externalwarnings "Off"

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

            table.insert(libs, 1, "asan");
            links {
                libs
            }

            sanitize {
                "address"
            }

            warnings "Extra" -- -Wall -Wextra
            externalwarnings "Off"

            disablewarnings {
                "unused-lambda-capture",

                -- GNU extensions
                "gnu-anonymous-struct",
                "nested-anon-types"
            }



project "pingforce_test"
    kind "ConsoleApp"
    targetname "test"

    files {
        "test/tests.cpp",
        "src/utils/**/*.cpp",
        "test/src/*.cpp"
    }

    includedirs {
        "test/include"
    }

    -- links {
    --     "asan"
    -- }

    externalincludedirs {
        "include"
    }

    -- sanitize {
    --     "address"
    -- }

    buildoptions {
        "-pedantic",
        "-gdwarf-4"
    }

    defines {
        "_PFTD_TEST",
        -- "_PFTD_DEBUG"
    }

    filter {"system:linux", "action:gmake"}
        symbols "On"
        optimize "Off"
        warnings "Extra"
        externalwarnings "Off"
