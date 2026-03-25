add_library(data_holder
    data_holder.c
)

target_link_libraries(data_holder
    PUBLIC
        data_source
        observer
)

target_include_directories(data_holder PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src/common
)
