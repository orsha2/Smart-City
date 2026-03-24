include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.6.1
)

FetchContent_MakeAvailable(unity)

FetchContent_Declare(
    fff
    GIT_REPOSITORY https://github.com/meekrosoft/fff.git
    GIT_TAG v1.0
    )
    
FetchContent_MakeAvailable(fff)

function(add_sc_unit_test test_name source_file tested_target)
    add_executable(${test_name} ${source_file})

    target_link_libraries(${test_name}
        PRIVATE
            ${tested_target}
            unity
            fff
    )

    add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${test_name}>)
endfunction()