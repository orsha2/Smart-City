add_library(entry_points
    entry_points.c
)

target_link_libraries(entry_points PUBLIC
    subject
)

target_include_directories(entry_points PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/hal
)