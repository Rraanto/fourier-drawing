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

#include "image.h"
#include "fourier.h"

#define GAP 25 // espace entre les textes

using namespace std;
using std::vector;
using std::complex;

vector<complex<double>> signal; // stockage donnees initiaux
vector<complex<double>> coefficients; // stockage coefficients tdf
vector<complex<double>> approx_trace; // stockage fonction resultante

int nb_coeffs;
double rotating_t = 0.0;
double DELTA = M_PI / 1000.0; // angle diff between frames
int is_rotating = 0; // animate or not
int showOriginalImage = 1;
int prePlotTrace = 1; // plot the trace beforehand
int showVectors = 0;
int TIMERSECS = 5;
int show_text = 1;

/* 
 * Fonction trigonometrique obtenue associées aux coefficients dans signal
 * i.e. la Série
 */
complex<double> F(double t);

/*
 * Store les F(t) (pour t 0..2 pi) dans un vecteur pour le nb de coeffs donné
 * partage l'interval en mm nombres que le signal initial reçu
 */
vector<complex<double>> computePts();

/*
 * Affiche la disposition des vecteurs a l'instant t;
 */
void renderVectors(double t);

void drawLine(double x_from, double y_from, double x_to, double y_to);

void drawFromComplex(complex<double> z, complex<double> origin);

void plotAxis(double x_min, double x_max, double y_min, double y_max);

void plotSignal(vector<complex<double>> signal);

void printText(double x, double y, void* font, char *txt);

void display();

void keyboard(unsigned char key, int x, int y);

void myInit();

void updateVectorPosition(int value);

vector<complex<double>> generate_signal(vector<vector<Point>> contour);

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
  approx_trace = computePts();
  if (prePlotTrace) {
    plotSignal(approx_trace);
  }

  // run openGL
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Discrete fourier transform");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(TIMERSECS, updateVectorPosition, 0);

  myInit();
  glutMainLoop();
}

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

/*
 * store F(0 ... 2pi) dans un tableau de complexes pour affichage
 * partage l'interval en mm nombres que le signal initial reçu
 */
vector<complex<double>> computePts() {
  vector<complex<double>> tmp;
  double delta = 2*M_PI / signal.size();
  for (int i = 0; i < signal.size(); i++) {
    double t = i * delta;
    complex<double> z = F(t);
    tmp.push_back(z);
  }
  return tmp;
}

/*
 * Affiche la disposition des vecteurs a l'instant t;
 */
void renderVectors(double t) {
  int N = coefficients.size();
  int m = N/2;

  complex<double> z;
  double x_origin = 0.0;
  double y_origin = 0.0;
  double x_to, y_to;

  for (int k = -m; k < m; k++) {
    double angle = k*t;
    z = coefficients[k+m] * complex<double>(cos(angle), sin(angle));
    x_to = x_origin + abs(z) * cos(arg(z));
    y_to = y_origin + abs(z) * sin(arg(z));

    double color_scale = 1.0 * (k+m) / N;
    glColor3f(0.0,(color_scale)*255, 255.0);
    drawLine(x_origin, y_origin, x_to, y_to);

    glBegin(GL_POINTS);
    glVertex2f(x_to, y_to);
    glEnd();

    x_origin = x_to;
    y_origin = y_to;
  }

}

void drawLine(double x_from, double y_from, double x_to, double y_to) {
  glBegin(GL_LINES);
  glVertex2f(x_from, y_from);
  glVertex2f(x_to, y_to);
  glEnd();
}

void drawFromComplex(complex<double> z, complex<double> origin) {
  double from_x = real(origin);
  double from_y = imag(origin);

  double to_y, to_x;
  // vecteur a partir du complexe
  double amplitude = abs(z);
  double angle = arg(z);

  to_x = from_x + amplitude * cos(angle);
  to_y = from_y + amplitude * sin(angle);
  drawLine(from_x, from_y, to_x, to_y);
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

void printText(double x, double y, void* font, char *txt) {
  glRasterPos2f(x, y);
  int i = 0;
  while (txt[i] != '\0') {
    glutBitmapCharacter(font, txt[i]);
    i++;
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0, 1.0, 1.0);
  if (showOriginalImage)
    plotSignal(signal);

  glColor3f(0.2, 0.2, 0.2);
  plotAxis(-1000, 1000, -1000, 1000);

  // affichage fonction
  glColor3f(0.0, 0.8, 0.6);
  
  if (show_text) {
    double gap = GAP;
    double left = -250.0;
    double right = 250.0;
    double top = 400;

    void* font = GLUT_BITMAP_HELVETICA_18;

    char tmp[128]; // store the text
    snprintf(tmp, sizeof(tmp), "signal de depart contenant: %d points", signal.size());
    printText(right, top, font, tmp);

    snprintf(tmp, sizeof(tmp), "N = %d", nb_coeffs);
    printText(left, top, font, tmp);

    snprintf(tmp, sizeof(tmp), "r: activer rotation (%d)", is_rotating);
    printText(left, top - gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "j/k: ajouter/reduire coefficients");
    printText(left, top - 2*gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "o: afficher original (%d)", showOriginalImage);
    printText(left, top - 3*gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "t: afficher approximation (%d)", prePlotTrace);
    printText(left, top - 4*gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "v: afficher epicycles (%d)", showVectors);
    printText(left, top - 5*gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "s/f: ralentir/accelerer");
    printText(right, top - gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "RPS %d", 1000/TIMERSECS);
    printText(right, top - 2*gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "h: afficher/masquer aide");
    printText(right, top - 3*gap, font, tmp);
  }
  int len, i;
  
  if (showVectors) {
    renderVectors(rotating_t);
  }
  else {
    is_rotating = 0;
  }

  int tranches = signal.size();
  double delta = 2*M_PI / tranches;
  
  if (prePlotTrace) {
    plotSignal(approx_trace);
  }

  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  switch(key) {
    case 'r': // enter key
      is_rotating = (is_rotating)?0:1;
      prePlotTrace = (prePlotTrace)?0:1; // masquer la trace pendant la rotation 
                                         // pour complexité
      glutPostRedisplay();
      break;
    case 'j': // reduce coeffs 
      nb_coeffs = nb_coeffs - 5;
      coefficients = tdf(signal, nb_coeffs);
      approx_trace = computePts();
      glutPostRedisplay();
      break;
    case 'k': // add coeffs
      nb_coeffs = nb_coeffs + 5;
      coefficients = tdf(signal, nb_coeffs);
      approx_trace = computePts(); 
      glutPostRedisplay();
      break;
    case 'o': // masquer/afficher image original 
      showOriginalImage = (showOriginalImage)?0:1;
      glutPostRedisplay();
      break;
    case 't': // masquer/afficher la trace préécrite
      prePlotTrace = (prePlotTrace)?0:1;
      glutPostRedisplay();
      break;
    case 'v':
      showVectors = (showVectors)?0:1;
      glutPostRedisplay();
      break;
    case 'f': // fasten
      if (TIMERSECS - 100 <= 0) TIMERSECS = 1;
      else TIMERSECS = TIMERSECS - 5;
      glutPostRedisplay();
      break;
    case 's': // fasten animation 
      TIMERSECS = TIMERSECS + 5;
      break;
    case 'h':
      show_text = (show_text)?0:1;
      glutPostRedisplay();
      break;
    case 27:
      exit(0);
      break;
  }
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

void updateVectorPosition(int value) {
  glutTimerFunc(TIMERSECS, updateVectorPosition, 1);
  if (is_rotating) {
    rotating_t = rotating_t + DELTA;
    glutPostRedisplay();
  }
}
