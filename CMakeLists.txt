# fourier_drawing initialization
cmake_minimum_required(VERSION 3.1)
project(fourier_drawing VERSION 1.0)

# add_executable(fourier_drawing src/Main.cpp)
# IMPORTANT: add executables from external libraries
add_executable(fourier_drawing src/Main.cpp libs/Fourier/fourier.cpp libs/Images/image.cpp)

# For local dependencies,
# The dependency MUST be installed in the computer
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# local libraries
add_library(Fourier libs/Fourier/fourier.h libs/Fourier/fourier.cpp)
add_library(Images libs/Images/image.h libs/Images/image.cpp)

# linking and libs directories
include_directories(fourier_drawing libs/Fourier libs/Images ${OpenCV_INCLUDE_DIRS} ${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(fourier_drawing ${OpenCV_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
