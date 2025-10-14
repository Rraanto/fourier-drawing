Animation illustrating [Fourier Fast Transform](https://fr.wikipedia.org/wiki/Transformation_de_Fourier_discr%C3%A8te) on contours from images interpreted as complex (2D) signals.

## Dependencies 
Building and compilation
- CMake (>= 3.1)

For the program:
- OpenCV2
- OpenGL
- GLUT

## Building and compilation
It is advised to store files related to a specific build in a standalone directory (for example `build/`). Once this is setup, go to that directory, and run 
```
cmake ..`
```
A `build/Makefile` should be generated, then go to `build/` and run `make`, then an executable `build/fourier_drawing` should be generated. 

## References
