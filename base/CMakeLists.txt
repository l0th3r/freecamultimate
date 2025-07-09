add_library(freecam_base STATIC)

target_sources(freecam_base
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.cpp
)

target_include_directories(freecam_base
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
