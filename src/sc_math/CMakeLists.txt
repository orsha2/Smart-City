add_library(sc_math    
    sc_math.c
)

target_include_directories(sc_math
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)