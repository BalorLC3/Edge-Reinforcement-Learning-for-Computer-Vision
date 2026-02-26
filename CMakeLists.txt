cmake_minimum_required(VERSION 3.10)
project(EdgeCVLib VERSION 1.0)

add_library(edgecv src/linalg/transforms.cpp)

target_include_directories(edgecv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(examples)
add_subdirectory(tests)
add_subdirectory(benchmarks)