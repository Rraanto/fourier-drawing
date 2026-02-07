# fourier_drawing initialization
cmake_minimum_required(VERSION 3.1)
project(fourier_drawing VERSION 1.0)

# executable
add_executable(fourier_drawing src/Main.cpp)

# For local dependencies,
# The dependency MUST be installed in the computer
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# local libraries
add_library(Fourier libs/Fourier/fourier.h libs/Fourier/fourier.cpp)
add_library(Images libs/Images/image.h libs/Images/image.cpp)
add_library(Utils libs/Utils/utils.h libs/Utils/utils.cpp)
add_library(App src/app.h src/app.cpp)

# linking and libs directories
include_directories(fourier_drawing libs/Fourier libs/Images libs/Utils ${OpenCV_INCLUDE_DIRS} ${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(fourier_drawing Fourier Images Utils App ${OpenCV_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
