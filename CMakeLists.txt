cmake_minimum_required(VERSION 3.16)

project(SmartCity C)

option(ENABLE_TESTING "Enable unit tests" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CompilerOptions)
apply_options()

add_subdirectory(src)

if(ENABLE_TESTING)
    add_subdirectory(tests)
endif()
