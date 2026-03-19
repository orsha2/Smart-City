add_subdirectory(observer)

add_executable(app
    main.c
)

target_link_libraries(app
    PRIVATE observer
    ${PROJECT_SOURCE_DIR}/common
)