find_package(OpenCV REQUIRED)

add_executable(test_linalg test_linalg.cpp)

target_link_libraries(test_linalg edgecv ${OpenCV_LIBS})