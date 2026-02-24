# Find OpenCV ONLY for the example apps
find_package(OpenCV REQUIRED)

# Create the executable
add_executable(interactive_transform szeliski_ex22_app.cpp)

# Link BOTH pure C++ library AND OpenCV to the app
target_link_libraries(interactive_transform edgecv ${OpenCV_LIBS})