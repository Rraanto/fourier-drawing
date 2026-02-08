#ifndef UTILS_H
#define UTILS_H

#include <GL/glut.h>
#include <complex>
#include <opencv2/opencv.hpp>
#include <vector>

using std::complex;
using std::vector;

/*
 * Calcule la valeur S_n (t) où S_n est le terme d'une série complexe
 * donnée par ses coefficients
 */
complex<double> computeSeriesValue(const vector<complex<double>> &coefficients,
                                   double t);

/*
 * calcule la courbe donnée par S_n(t) pour une période complète
 */
vector<complex<double>>
computePoints(const vector<complex<double>> &signal,
              const vector<complex<double>> &coefficients);

/*
 * Fonctions d'afficahges utilitaires
 */
void drawLine(double x_from, double y_from, double x_to, double y_to);
void plotAxis(double x_min, double x_max, double y_min, double y_max);
void plotSignal(const vector<complex<double>> &signal);
void printText(double x, double y, void *font, const char *txt);
void renderVectors(const vector<complex<double>> &coefficients, double t);

vector<complex<double>>
generateSignal(const vector<vector<cv::Point>> &contour);

#endif
