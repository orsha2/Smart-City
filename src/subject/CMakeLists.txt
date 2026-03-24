add_library(subject    
    subject.c
)

target_link_libraries(subject
    PUBLIC
        observer
)

target_include_directories(subject PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/observer
)