cmake_minimum_required(VERSION 3.14)
project(FallingParticles C)

set(BUILD_SHARED_LIBS OFF)
option(BUILD_COLOR_TEST "Build the color testing tool" OFF)
option(FETCH_RAYLIB "Download raylib during configure if not found" ON)

find_package(raylib QUIET CONFIG)

if (NOT raylib_FOUND)
    if (FETCH_RAYLIB)
        include(FetchContent)
        message(STATUS "raylib package config not found. Fetching raylib from source...")
        FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5.5
        )
        FetchContent_MakeAvailable(raylib)
    else()
        message(FATAL_ERROR
            "raylib package config not found. Set raylib_DIR or CMAKE_PREFIX_PATH to a raylib install, or enable FETCH_RAYLIB.")
    endif()
endif()

add_executable(FallingParticles
    src/main.c
    src/particle.c
    src/colorManager.c
)
target_link_libraries(FallingParticles PRIVATE raylib)

if (BUILD_COLOR_TEST)
    add_executable(ColorTest
        test/color_test.c
        src/colorManager.c
    )
    target_link_libraries(ColorTest PRIVATE raylib)
endif()