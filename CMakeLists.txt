cmake_minimum_required(VERSION 3.16)

project(SmartCity C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(cmake/CompilerOptions.cmake)
include(cmake/Dependencies.cmake)
include(cmake/Testing.cmake)

add_subdirectory(src)
add_subdirectory(tests)