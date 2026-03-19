add_executable(test_sc_math
    test_sc_math.c
)

target_link_libraries(test_sc_math
    PRIVATE
        sc_math
        unity
)

add_test(NAME test_sc_math COMMAND test_sc_math)