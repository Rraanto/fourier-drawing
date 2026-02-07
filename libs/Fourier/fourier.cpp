#include "fourier.h"
#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>

using namespace std;
using std::complex;
using std::vector;

vector<complex<double>> tdf(vector<complex<double>> S, int NB_COEFFS) {
  /*
   * calcule la transformée de Fourier à partir d'un signal complexe S
   * S: un ensemble de nombres complexes (x, y)
   */
  vector<complex<double>> res;
  int N = S.size();
  int m = N / 2;
  int sup = NB_COEFFS / 2;

  for (int k = -sup; k < sup; k++) {
    complex<double> z(0.0, 0.0); // somme

    // intégration discrete
    for (int n = -m; n < m; n++) {
      complex<double> x = S[n + m]; // facteur de l'exp dans le coeff
      double angle = 2.0 * (double)k * M_PI * (double)n / (double)N;
      z += x * complex<double>(cos(angle) / N, -sin(angle) / N);
    }
    res.push_back(z);
  }
  return res;
}
