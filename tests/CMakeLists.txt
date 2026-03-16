add_executable(test_math
    math/test_math.c
)

target_link_libraries(test_math
    PRIVATE
        math
        unity
)

target_include_directories(test_math
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/math
)

add_test(NAME test_math COMMAND test_math)