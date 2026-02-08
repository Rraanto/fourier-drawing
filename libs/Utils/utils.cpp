#include "utils.h"

#include <cmath>

complex<double> computeSeriesValue(const vector<complex<double>> &coefficients,
                                   double t) {
  // calcule la valeur S_n(t) où S_n est une  transformée de fourier
  // discrète donnée par ses coefficients
  // essentiellement multiplie tout simplement par exp(k(t))
  complex<double> value(0.0, 0.0);
  int N = coefficients.size();
  int m = N / 2;
  for (int k = -m; k < m; k++) {
    double angle = k * t;
    value =
        value + coefficients[k + m] * complex<double>(cos(angle), sin(angle));
  }
  return value;
}

vector<complex<double>>
computePoints(const vector<complex<double>> &signal,
              const vector<complex<double>> &coefficients) {
  vector<complex<double>> tmp;
  if (signal.empty()) {
    return tmp;
  }

  // subdivisions du temps
  int subdivisions_temps =
      1000; // influe uniquement la résolution de la courbe estimée
  double delta = 2.0 * M_PI / (double)subdivisions_temps;
  for (int i = 0; i < subdivisions_temps; i++) {
    double t = i * delta;
    complex<double> z = computeSeriesValue(coefficients, t);
    tmp.push_back(z);
  }
  return tmp;
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

void plotSignal(const vector<complex<double>> &signal) {
  glBegin(GL_POINTS);
  for (complex<double> z : signal) {
    glVertex2f(real(z), imag(z));
  }
  glEnd();
}

void printText(double x, double y, void *font, const char *txt) {
  glRasterPos2f(x, y);
  for (int i = 0; txt[i] != '\0'; i++) {
    glutBitmapCharacter(font, txt[i]);
  }
}

void renderVectors(const vector<complex<double>> &coefficients, double t) {
  int N = coefficients.size();
  int m = N / 2;
  double x_origin = 0.0;
  double y_origin = 0.0;
  double x_to, y_to;

  for (int k = -m; k < m; k++) {
    double angle = k * t;
    complex<double> z =
        coefficients[k + m] * complex<double>(cos(angle), sin(angle));
    x_to = x_origin + abs(z) * cos(arg(z));
    y_to = y_origin + abs(z) * sin(arg(z));

    double color_scale = 1.0 * (k + m) / N;
    glColor3f(0.0, (color_scale) * 255, 255.0);
    drawLine(x_origin, y_origin, x_to, y_to);

    glBegin(GL_POINTS);
    glVertex2f(x_to, y_to);
    glEnd();

    x_origin = x_to;
    y_origin = y_to;
  }
}

vector<complex<double>>
generateSignal(const vector<vector<cv::Point>> &contour) {
  /*
   * tranforme un ensemble de points en signal complexe
   * recentrée à l'origine
   */
  double x_min = contour[0][0].x;
  double y_min = contour[0][0].y;
  double x_max = x_min;
  double y_max = y_min;
  vector<complex<double>> signal;

  for (cv::Point p : contour[0]) {
    if (p.x <= x_min)
      x_min = p.x;
    if (p.y <= y_min)
      y_min = p.y;
    if (p.x >= x_max)
      x_max = p.x;
    if (p.y >= y_max)
      y_max = p.y;
    signal.push_back(complex<double>(p.x, p.y));
  }

  double x_centre = (x_max - x_min) / 2.0;
  double y_centre = (y_max - y_min) / 2.0;
  for (int i = 0; i < signal.size(); i++) {
    signal[i] = signal[i] - complex<double>(x_centre, y_centre);
  }

  return signal;
}
