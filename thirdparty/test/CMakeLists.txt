cmake_minimum_required(VERSION 3.20)
project(DX11MinimalApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(dx11_test WIN32 src/main.cpp)
target_link_libraries(dx11_test d3d11)
