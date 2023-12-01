#ifndef FOURIER_H
#define FOURIER_H

#include "nombres_complexes.h"

/*
 * Calcule une approximation par calcul numérique de l'intégrale d'une fonction donnée en argument
 */
complexe integrer(float a, float b, complexe(*func)(float t));

#endif
