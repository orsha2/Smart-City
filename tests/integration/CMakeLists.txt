add_executable(test_temperature_pipeline
    test_temperature_pipeline.c
)

target_link_libraries(test_temperature_pipeline
    PRIVATE
        entry_points
        data_holder
        unity
)

target_include_directories(test_temperature_pipeline
    PRIVATE
        ${fff_SOURCE_DIR}
)

add_test(NAME test_temperature_pipeline COMMAND $<TARGET_FILE:test_temperature_pipeline>)
