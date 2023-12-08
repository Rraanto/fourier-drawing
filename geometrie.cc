#include <vector>
#include <cmath>

#include "geometrie.h"
#include "nombres_complexes.h"

using namespace std;
using std::vector;

/*
 * retourne la position du vecteur par rapport a un origine a un instant t
 */
Point2d get_position(Vecteur v, float t, Point2d origine) {
  float x = origine.x + v.norme * cos(t * v.veloc + v.angle);
  float x = origine.y + v.norme * sin(t * v.veloc + v.angle);
  return Point2d(x, y);
}

/*
 * retourne la position du dernier vecteur dans une liste de vecteurs, a un instant t
 */
Point2d get_end_position(vector<Vecteur> L, float t) {
  return Point(0.0, 0.0);
}
