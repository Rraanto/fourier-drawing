#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/glut.h>
#include <vector>
#include <opencv2/opencv.hpp>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "nombres_complexes.h"
#include "utils.h"
#include "image.h"

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

  if (argc != 2) {
    cout << "add exactly one (01) path to an image as argument\n";
    return(1);
  }

  Mat img = imread(argv[1]);
  vector<complexe> signal = generer_signal(contour_plus_long(img));

  cout << "Signal de taille " << signal.size() << "\n";
}
