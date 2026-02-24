cmake_minimum_required(VERSION 3.10)
project(EdgeCVLib VERSION 1.0)

# Define the library 
add_library(edgecv src/linalg/linalg.cpp)

# Expose the include folder
target_include_directories(edgecv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Move on to building the examples
add_subdirectory(examples)