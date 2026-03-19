function(apply_options)
    set(CMAKE_C_STANDARD 99 PARENT_SCOPE)
    set(CMAKE_C_STANDARD_REQUIRED ON PARENT_SCOPE)
    set(CMAKE_C_EXTENSIONS OFF PARENT_SCOPE)

    add_compile_options(
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
endfunction()
