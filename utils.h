#ifndef UTILS_H
#define UTILS_H

#include <vector>

#include "nombres_complexes.h"

using std::vector;

/*
 * Fichier header du module utils, contenant l'interface entre l'animation graphique avec openGL et les nombres complexes
 * contient également les fonctions utilitaires implémentées
 */

/*
 * *****************************************************************************
 * fonctions interfaces openGL/nombres_complexes
 * *****************************************************************************
 */

/*
 * Type structuré epicycle, encodant les informations requises pour un vecteur rotatif
 */
struct epicycle {
  float length, initial_angle, rotation_speed;
  epicycle(float l, float t, float v):length(l), initial_angle(t), rotation_speed(v) {};
};

/*
 * *****************************************************************************
 * fonctions utilitaires
 * *****************************************************************************
 */

/*
 * créé un vecteur de taille n, avec des nombres comprises entre a et b
 */
vector<float> float_linspace(float begin, float end, int n);

#endif
