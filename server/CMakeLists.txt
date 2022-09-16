cmake_minimum_required(VERSION 3.0.0)
project(server
    VERSION 0.0.1
    DESCRIPTION "Balanceador de carga usando la librería ZMQ"
    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
add_executable(server src/server.cpp)
target_link_libraries(server zmq)
target_compile_features(server PRIVATE cxx_std_20)
target_compile_options(server PRIVATE -Wall -Wextra -Wpedantic)
