cmake_minimum_required(VERSION 3.16)

project(SmartCity C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(cmake/CompilerOptions.cmake)
include(cmake/Dependencies.cmake)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(cmake/Testing.cmake)
endif()

add_subdirectory(src)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory(tests)
endif()