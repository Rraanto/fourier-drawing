#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

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
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;

  // to simulate noisy data
  findContours(image, contours, hierarchy, RETR_EXTERNAL,
               CHAIN_APPROX_TC89_KCOS);

  // trouver le contour le plus long
  int max_index, max_value = 0;
  i = 0;
  for (vector<Point> contour : contours) {
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
