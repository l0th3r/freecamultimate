add_library(freecam_dll SHARED)

target_sources(freecam_dll
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dll_main.cpp
)

target_link_libraries(freecam_dll
    PRIVATE
        freecam_base
        backend_dx11
        minhook
)

target_include_directories(freecam_dll
    PRIVATE
        ${CMAKE_SOURCE_DIR}/base/inc
)
