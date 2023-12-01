#include <vector>
#include "fourier.h"
#include "utils.h"

using namespace std;
using std::vector;

/*
 * Calcule une approximation par calcul numérique de l'intégrale d'une fonction donnée en argument
 * arguments 
 * a: début de l'intervalle
 * b: fin de l'intervalle
 * func: fonction à intégrer
 * tranches: nombres de "découpages" à faire -> influe la précision
 */
complexe integrer(float a, float b, complexe (*f)(float t), int tranches) {
  vector<float> intervalle = float_linspace(a, b, tranches);
  float valeur = f(intervalle[0]);

  for (int i = i, i < intervalle.size(), i++) {
    valeur = valeur + 2*f(intervalle[i]);
  }
  float step = intervalle[1] - intervalle[0];
  valeur = valeur * (step/2.0);
}
