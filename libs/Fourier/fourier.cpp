#include <vector>
#include <cmath>
#include <complex>
#include "fourier.h"

using namespace std;
using std::vector;
using std::complex;

vector<complex<double>> tdf(vector<complex<double>> S, int NB_COEFFS) {
  vector<complex<double>> res;
  int N = S.size();
  int m = N/2;
  int sup = NB_COEFFS/2;
  for (int k = -sup; k < sup; k++) {
    complex<double> z(0.0, 0.0); // somme
    for (int n = -m; n < m; n++) {
      complex<double> x = S[n + m]; // facteur de l'exp dans le coeff 
      double angle = 2*k*M_PI*n/N;
      z = z + x * complex<double>(cos(angle) / N, -sin(angle) / N);
    }
    res.push_back(z);
  }
  return res;
}
