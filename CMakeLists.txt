cmake_minimum_required(VERSION 3.26.4)
set(CMAKE_CXX_STANDARD 13)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(logic_flow VERSION 1.0)
add_executable(logic_flow main.cpp)
target_include_directories(logic_flow PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

