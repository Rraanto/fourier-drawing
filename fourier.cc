#include <vector>
#include <cmath>
#include "fourier.h"
#include "utils.h"

using namespace std;
using std::vector;

vector <complexe> tdf(vector<complexe> S) {
  vector<complexe> transform;

  // variables locales
  float angle;
  int k, n;
  int N = S.size();
  for (k = 0; k < N; k++) {
    complexe sum = complexe(0, 0);
    for (n = 0; n < N; n++) {
      angle = -2*M_PI*k*n/N;
      sum = sum + (S[n] * complexe(cos(angle), sin(angle)));
    }
    transform.push_back(sum);
  }
  return transform;
}
