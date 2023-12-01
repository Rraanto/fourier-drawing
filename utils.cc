#include <vector>

#include "utils.h"

using namespace std;

/*
 * créé un vecteur de taille n, avec des nombres comprises entre a et b
 */
vector<float> float_linspace(float begin, float end, int n){
  vector<float> res;
  if (n == 1) res.push_back(begin);
  else {
    float delta = (end - begin) / (n - 1);

    for (int i = 0; i < n- 1; i++) {
      res.push_back(begin + delta*i);
    }
  }
  return res;
}
