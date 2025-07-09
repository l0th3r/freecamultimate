cmake_minimum_required(VERSION 3.20)
project(FreecamUltimate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(USE_BACKEND "dx11" CACHE STRING "Backend graphique à utiliser")
add_subdirectory(backend/${USE_BACKEND})

# dep
add_subdirectory(thirdparty/minhook)
add_subdirectory(thirdparty/imgui)

# local
add_subdirectory(base)
add_subdirectory(dll_entry)
