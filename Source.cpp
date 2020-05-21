#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv_modules.hpp>
#include <stdint.h>

using namespace std;
using namespace cv;

int main(int argv, char** argc)
{
	int s0 = 190 ; //threshold
	int morph_elem = 2; //parameter to adjust morphological opening
	int morph_size = 70;//parameter to adjust morphological opening

	try {
		Mat original = imread("Capture.png", IMREAD_GRAYSCALE); //original image in greyscale
		Mat modified = imread("Capture.png", IMREAD_GRAYSCALE); //image to be altered
		Mat thd, morph, stats, centroids, labelImage;
		Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
		
		threshold(modified, thd, s0, 255, THRESH_BINARY); //conducting binary thresholding
		morphologyEx(thd, morph, 2,element);			  //conducting morphological opening to denoise
		int nLabels = connectedComponentsWithStats(morph, labelImage, stats, centroids, 8, CV_32S); //counting how many objects are in the image

		imshow("original", original); //original image
		imshow("threshold", thd); //thresholding image
		imshow("morph", morph); //image after subjected to morphological opening

		int numberofbreadinthisimage = nLabels - 1;//counter for how many bread

		cout << "Number of bread in this image is: " << nLabels - 1 <<endl;
		waitKey(0);
		return 0;
	}
	catch (Exception a)
	{
		return 0;
	};
};
