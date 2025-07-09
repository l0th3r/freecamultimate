add_library(backend_dx11 STATIC)

target_sources(backend_dx11
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/present_hook.cpp
)

target_include_directories(backend_dx11
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(backend_dx11
    PRIVATE
        minhook
        imgui
)
