#include <cmath>
#include <cstdlib>
#include <iostream>

#include <GL/glut.h>
#include <opencv2/opencv.hpp>

#include "app.h"
#include "fourier.h"
#include "image.h"
#include "utils.h"

using namespace cv;
using namespace std;
using std::vector;

void myInit();

int main(int argc, char **argv) {
  AppState state;
  state.delta = M_PI / 1000.0;
  state.timer_msecs = 5;
  state.pre_plot_trace = 1;
  state.show_original_image = 1;
  state.show_vectors = 0;
  state.show_text = 1;

  if (argc == 1 || argc > 3) {
    cout << "requires exactly one (01) argument, a path to an image file";
    exit(0);
  }

  Mat image = imread(argv[1]);
  vector<vector<Point>> contour = contour_plus_long(image);
  state.signal = generateSignal(contour);

  if (argc == 3) {
    state.nb_coeffs =
        stoi(argv[2]); // if theres a starting amount of coefficients desired
  }

  state.coefficients = tdf(state.signal, state.nb_coeffs);
  state.approx_trace = computePoints(state.signal, state.coefficients);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Discrete fourier transform");
  registerAppCallbacks(state);

  myInit();
  glutMainLoop();
}

void myInit() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);
  glPointSize(1.5);
  glLineWidth(2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-780, 780, -420, 420);
}
