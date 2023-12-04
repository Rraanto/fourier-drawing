#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>

#include "nombres_complexes.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

/* 
 * module image 
 * Permet l'obtention du signal a traiter a partir d'un fichier image
 */

/*
 * calcule le contour le plus long a partir d'un objet image
 */
vector<vector<Point>> contour_plus_long(Mat image);

/* 
 * Genere le signal a traiter a partir d'un contour
 * TODO: "Projeter" le contour pour que le contour commence en 0, 0 avant la conversion en complexes
 */
vector<complexe> generer_signal(vector<vector<Point>> contour);

#endif
