#include <iostream>
#include <fstream>
#include <cmath>

#include "nombres_complexes.h"

using namespace std;

int main(int argc, char **argv) {
  complexe z = complexe(0, 1); // le nombre i
  affiche(z);
  cout << "\n";
  affiche(z - complexe(1, 0));
  cout << "\n";
  affiche(conj(z - complexe(1, 0)));
  cout << "\n";
  cout << mod(conj(z - complexe(1, 0)));
  cout << "\n";

  complexe x = polar(1, M_PI/3);
  affiche(x);
}
