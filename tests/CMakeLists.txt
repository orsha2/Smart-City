add_executable(test_math
    math/test_math.c
)

target_link_libraries(test_math
    PRIVATE
        math
        unity
)

add_test(NAME test_math COMMAND test_math)