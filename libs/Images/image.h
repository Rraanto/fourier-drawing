#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include <vector>

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
vector<vector<Point>> contour_plus_long(Mat image);
#endif
