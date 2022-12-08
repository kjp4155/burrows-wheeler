cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(BWT LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_compile_options(-O3 -std=c++14 -g -Wall -Wno-unused-result)

include_directories(".")

add_subdirectory(spdlog)
add_subdirectory(utils)
add_subdirectory(engines)

if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()

file(GLOB CPP_SOURCES "*.cpp")
add_executable(main ${CPP_SOURCES})

target_link_libraries(main PRIVATE spdlog::spdlog utils engines)