#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "math.h"

#include "nombres_complexes.h"
#include "utils.h"
#include "image.h"
#include "fourier.h"
using namespace std;

using std::vector;

vector <complexe> signal;
vector<vector<Point>> contours;

const float PI = 3.14159265359;

// Fourier series parameters
std::vector<float> frequencies = {0, 1, 2, 3, 4}; // Frequencies of epicycles
std::vector<float> amplitudes={0, 1, 2, 3, 4}; // Frequencies of epicycles // Amplitudes of epicycles

// Function to calculate the Fourier series coefficients
void calculateEpicycle(float t, float& x, float& y) {
    x = 0;
    y = 0;
    for (std::size_t i = 0; i < frequencies.size(); ++i) {
        float angle = frequencies[i] * t;
        x += amplitudes[i] * std::cos(angle);
        y += amplitudes[i] * std::sin(angle);
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white

    glBegin(GL_LINE_STRIP);

    for (float t = 0; t <= 2 * PI; t += 0.01) {
        float x, y;
        calculateEpicycle(t, x, y);
        glVertex2f(x + 400, y + 400); // Offset for centering
    }

    glEnd();

    glFlush();
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set clear color to black
    gluOrtho2D(0.0, 800.0, 0.0, 800.0); // Set up the coordinate system
}

int main(int argc, char** argv) {
  /*
  Mat img = imread(argv[1]);
    signal = tdf(generer_signal(contour_plus_long(img)));
    int n = 0;
    for (complexe z: signal) {
      frequencies.push_back(pow(-1, n)2*n);
      amplitudes.push_back(mod(z));
    }
    */

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Epicycle Tracing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
