include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.6.1
)

FetchContent_MakeAvailable(unity)

function(add_sc_unit_test test_name source_file tested_target)
    add_executable(${test_name} ${source_file})

    target_link_libraries(${test_name}
        PRIVATE
            ${tested_target}
            unity
    )

    add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${test_name}>)
endfunction()