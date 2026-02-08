Started as a mere illustration of [Fourier Fast Transform](https://fr.wikipedia.org/wiki/Transformation_de_Fourier_discr%C3%A8te) inspired by [3blue1Brown](https://www.3blue1brown.com/). 

This may evolve more towards a DFT-based contour or region reconstruction from noisy data. 

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
