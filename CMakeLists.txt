cmake_minimum_required(VERSION 3.0)
project(FallingSand)

find_package(raylib CONFIG REQUIRED)

add_executable(FallingSand src/falling_sand.c)
target_link_libraries(FallingSand PRIVATE raylib)