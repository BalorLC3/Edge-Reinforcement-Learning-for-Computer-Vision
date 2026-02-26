find_package(OpenCV REQUIRED)

add_executable(interactive_transform szeliski_ex22_app.cpp)

target_link_libraries(interactive_transform edgecv ${OpenCV_LIBS})