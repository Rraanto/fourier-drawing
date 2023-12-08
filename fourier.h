#ifndef FOURIER_H
#define FOURIER_H

#include <vector>
#include <complex>

using std::vector;
using std::complex;

/*
 * Calcule la transformee de fourier discrete a partir d'un signal S
 */
vector<complex<double>> tdf(vector<complex<double>> S, int NB_COEFFS);

#endif
