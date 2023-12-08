#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "nombres_complexes.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using std::vector;

/* 
 * module image 
 * Permet l'obtention du signal a traiter a partir d'un fichier image
 */

/*
 * calcule le contour le plus long a partir d'un objet image
 */
vector<vector<Point>> contour_plus_long(Mat image) {
  int i;

  // pré-traitement de l'image (inversion/nuance de gris, seuil)
  flip(image, image, 0);
  cvtColor(image, image, COLOR_BGR2GRAY);
  threshold(image, image, 150, 255, THRESH_BINARY);

  image = 255 - image;

  // trouver les contours
  vector<vector<Point>>contours;
  vector<Vec4i> hierarchy;

  findContours(image, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
  
  // trouver le contour le plus long
  int max_index, max_value = 0;
  i = 0;
  for (vector<Point> contour: contours) {
    if (contour.size() >= max_value) {
      max_value = contour.size();
      max_index = i;
    }
    i++;
  }
  
  vector<Point> tmp(contours[max_index]);
  vector<vector<Point>> res = {tmp};

  return res;
}

/* 
 * Genere le signal a traiter a partir d'un contour
 * TODO: "Projeter" le contour pour que le contour commence en 0, 0 avant la conversion en complexes
 */
vector<complexe> generer_signal(vector<vector<Point>> contour) {
  vector<complexe> res;
  
  // calcul du point le plus proche de l'origine (0, 0)
  int min_x = contour[0][0].x;
  int min_y = contour[0][0].y;

  for (Point p: contour[0]) {
    if (p.x <= min_x) min_x = p.x;
    if (p.y <= min_y) min_y = p.y;
  }
  int i = 0;
  for (Point p: contour[0]) {
    complexe z = complexe(p.x - min_x, p.y - min_y);
    res.push_back(z);
    i++;
  }

  return res;
}
