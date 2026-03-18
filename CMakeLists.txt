cmake_minimum_required(VERSION 3.16)

project(SmartCity C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompilerOptions)
include(Testing)

add_subdirectory(src)
