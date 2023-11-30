#include <iostream>
#include <cmath>

#include "nombres_complexes.h"

using namespace std;


/*
 * définition des opérations de base
 */

complexe operator + (const complexe &x, const complexe &y){
  return complexe(x.re + y.re, x.im + y.im);
}

complexe operator * (const complexe &x, const complexe &y) {
  return complexe(x.re*y.re - x.im*y.im, x.re*y.im + x.im*y.re);
}

complexe operator - (const complexe &x, const complexe &y) {
  return complexe(x.re - y.re, x.im-y.im);
}

/*
 * Fonctions basiques sur les complexes
 */

/*
 * Calcule le conjugué d'un nombre complexe
 * argument: complexe z
 * valeur de retour: conjugué de z
 */
complexe conj(complexe z) {
  return complexe(z.re, -z.im);
}

/*
 * Calcule le module d'un complexe z
 */
float mod(complexe z) {
  if (z.im == 0.0) return z.re; 
  else return sqrt(pow(z.re, 2) + pow(z.re, 2));
}

/*
 * Calcule l'argument d'un complexe z
 */
float arg(complexe z) {
  return atan(z.im / z.re);
}

/*
 * Retourne le complexe a partir d'une forme polaire 
 * arguments: r, réel positif module du complexe
 *            theta: réel argument du complexe 
 * retourne: (r.cos(theta), r.sin(theta)) (Formule d'Euler)
 */
complexe polar(float r, float theta) {
  return complexe(r*cos(theta), r*sin(theta));
}
/* affiche le complexe z */ 
void affiche(complexe z) {
  cout << z.re << " + i(" << z.im << ")";
}
