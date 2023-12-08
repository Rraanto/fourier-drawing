#ifndef GEOMETRIE_H
#define GEOMETRIE_H

/*
 * Fichier header contenant l'implémentation des types manipulés pour la géometrie
 */

struct Point2d {
  float x;
  float y;
  Point2d(float i, float j):x(i), y(j) {}
};

/*
 * Definition d'un vecteur rotatif
 * contenant une norme, une cadence de rotation et un angle de départ
 */
struct Vecteur {
  float norme;
  float veloc;
  float angle;
  Vecteur(float n, float v, float t): norme(n), veloc(v), angle(t){}
};

/*
 * retourne la position du vecteur par rapport a un origine a un instant t
 */
Point2d get_position(Vecteur v, float t, Point2d origine);

/*
 * retourne la position du dernier vecteur dans une liste de vecteurs, a un instant t
 */
Point2d get_end_position(vector<Vecteur>, float t);

#endif
