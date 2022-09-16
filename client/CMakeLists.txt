cmake_minimum_required(VERSION 3.0.0)
project(client
    VERSION 0.0.1
    DESCRIPTION "Cliente de pruebas ZMQ"
    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
add_executable(client src/client.cpp)
target_link_libraries(client zmq)
target_compile_features(client PRIVATE cxx_std_20)
target_compile_options(client PRIVATE -Wall -Wextra -Wpedantic)
