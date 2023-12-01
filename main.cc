#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/glut.h>
#include <vector>

#include "nombres_complexes.h"
#include "utils.h"

using namespace std;
using std::vector;

void display() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_QUADS);
  glColor3f(1.0f, 1.0f, 1.0f); // color

  // x, y
  glVertex2f(-0.5f, -0.5f);
  glVertex2f(0.5f, -0.5f);
  glVertex2f(0.5f, 0.5f);
  glVertex2f(-0.5f, 0.5f);

  glEnd();

  glFlush(); // rendering
}

int main(int argc, char **argv) {
  /*
  glutInit(&argc, argv);
  glutCreateWindow("openGL setup test");
  glutInitWindowSize(320, 320);
  glutInitWindowPosition(50, 50);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
  */

  complexe z = complexe(1, 1);
  affiche(z / 2);
  cout << "\n";

  affiche (1 / z);
  cout << "\n";

  affiche(2 * z);
  cout << "\n";

  affiche(z * 2);
  cout << "\n";
}
