#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/glut.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <string>
#include <complex>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "utils.h"
#include "image.h"
#include "fourier.h"

using namespace std;
using std::vector;
using std::complex;

vector<complex<double>> signal; // stockage donnees initiaux
vector<complex<double>> coefficients; // stockage coefficients tdf

int nb_coeffs;

/* 
 * Fonction trigonometrique obtenue associées aux coefficients dans signal
 * i.e. la Série
 */
complex<double> F(double t) {
  complex<double> value(0.0, 0.0);
  int N = coefficients.size();
  int m = N/2;
  for (int k = -m; k < m; k++) {
    double angle = k*t;
    value = value + coefficients[k+m] * complex<double>(cos(angle), sin(angle));
  }
  return value;
}

void drawLine(double x_from, double y_from, double x_to, double y_to) {
  glBegin(GL_LINES);
  glVertex2f(x_from, y_from);
  glVertex2f(x_to, y_to);
  glEnd();
}

void plotAxis(double x_min, double x_max, double y_min, double y_max) {
  drawLine(x_min, 0.0, x_max, 0.0);
  drawLine(0.0, y_min, 0.0, y_max);
}

void plotSignal(vector<complex<double>> signal) {
  glBegin(GL_POINTS);
  for (complex<double> z: signal) {
    glVertex2f(real(z), imag(z));
  }
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0, 1.0, 1.0);
  plotSignal(signal);

  glColor3f(0.2, 0.2, 0.2);
  plotAxis(-1000, 1000, -1000, 1000);

  // affichage fonction
  glColor3f(0.0, 0.8, 0.6);
  int tranches = 10000;
  double delta = 2*M_PI / tranches;

  glBegin(GL_POINTS);
  for (int i = 0; i < tranches; i++) {
    double t = i*delta;
    complex<double> z = F(t);
    glVertex2f(real(z), imag(z));
  }
  glEnd();

  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  switch(key) {
    case ' ':
      nb_coeffs = nb_coeffs + 10;
      coefficients = tdf(signal, nb_coeffs);
      glutPostRedisplay();
      break;
    case 27:
      exit(0);
  }
}

void myInit() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);
  glPointSize(2.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-780, 780, -420, 420);
}

vector<complex<double>> generate_signal(vector<vector<Point>> contour) {
  // calculer x minimum et y pour centrer les coordonnees a l'origine
  double x_min = contour[0][0].x;
  double y_min = contour[0][0].y;
  double x_max = x_min;
  double y_max = y_min;
  vector<complex<double>> signal;
  for (Point p: contour[0]) {
    if (p.x <= x_min) x_min = p.x;
    if (p.y <= y_min) y_min = p.y;
    if (p.x >= x_max) x_max = p.x;
    if (p.y >= y_max) y_max = p.y;
    complex<double> z(p.x, p.y);
    signal.push_back(z);
  }

  // centrage des coordonnees
  double x_centre = (x_max - x_min) / 2.0;
  double y_centre = (y_max - y_min) / 2.0;
  for (int i = 0; i < signal.size(); i++) {
    signal[i] = signal[i] - complex<double>(x_centre, y_centre);
  }
  return signal;
}

int main(int argc, char **argv) {
  if (argc == 1 || argc > 3) {
    cout << "requires exactly one (01) argument, a path to an image file";
    exit(0);
  }

  if (argc == 3) {
    nb_coeffs = stoi(argv[2]);
  }


  // read image, store contour and generate complex signal
  Mat image = imread(argv[1]);
  vector<vector<Point>> contour = contour_plus_long(image);
  signal = generate_signal(contour);
  coefficients = tdf(signal, nb_coeffs);

  // run openGL
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Discrete fourier transform");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  myInit();
  glutMainLoop();
}
