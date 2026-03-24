add_library(observer    
    observer.c
)

target_include_directories(observer PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src/common
)