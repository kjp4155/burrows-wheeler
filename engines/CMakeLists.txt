cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE CPP_SOURCES "*.cpp")

add_library(engines SHARED ${CPP_SOURCES})
target_link_libraries(engines PRIVATE spdlog::spdlog utils)