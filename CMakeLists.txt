cmake_minimum_required(VERSION 3.26.4)

project(logic_flow VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(logic_flow ${SOURCES})

# Generate compile_commands.json (doesn't work on my system for some reason, use "cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1" when compiling)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)