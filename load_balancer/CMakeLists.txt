cmake_minimum_required(VERSION 3.0.0)
project(load_balancer
    VERSION 0.0.1
    DESCRIPTION "Balanceador de carga usando la librería ZMQ"
    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
add_executable(load_balancer src/load_balancer.cpp)
target_link_libraries(load_balancer zmq)
target_compile_features(load_balancer PRIVATE cxx_std_20)
target_compile_options(load_balancer PRIVATE -Wall -Wextra -Wpedantic)
