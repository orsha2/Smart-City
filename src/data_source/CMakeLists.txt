add_library(data_source
    data_source.c
)

target_link_libraries(data_source
    PUBLIC
        subject
)

target_include_directories(data_source PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/hal
)
