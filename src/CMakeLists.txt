add_subdirectory(sc_math)

add_executable(app
    main.c
)

target_link_libraries(app
    PRIVATE sc_math
)