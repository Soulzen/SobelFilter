#pragma once

#include <opencv2/core.hpp>

using namespace cv;

class Sobel
{

private:

	Mat *image;				//Imagen de origen
	int rows, cols;			
	int* img_h, * img_v;
	double *img_t;
	uchar* img_f;
	double max = -5000000.0f, min = 5000000.0f;

	int Gx[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int Gy[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };

public:

	Mat* imageOut;

	Sobel(Mat *image);

	void ProcessX();
	void ProcessY();
	void ProcessT();
	void ProcessF();
	void WriteImg();

};

