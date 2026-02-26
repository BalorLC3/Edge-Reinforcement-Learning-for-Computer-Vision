find_package(OpenCV REQUIRED)

add_executable(latency latency.cpp)

target_link_libraries(latency edgecv ${OpenCV_LIBS})