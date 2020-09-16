#include <iostream>

#include "Sobel.h"

using namespace std;

Sobel::Sobel(Mat *image) {
	this->image = image;
	rows = image->rows,
	cols = image->cols;
	img_h = new int[(rows-2) * (cols-2)];
	img_v = new int[(rows - 2) * (cols - 2)];
	img_t = new double[(rows - 2) * (cols - 2)];
	img_f = new uchar[(rows - 2) * (cols - 2)];
	imageOut = new Mat(rows-2, cols-2, CV_8UC1);

}

// Process X - Pasa el filtro en horizonatal
void Sobel::ProcessX()
{
	int frame[3][3];

	for (int y = 1; y < rows-1; y++) {
		for (int x = 1; x < cols-1; x++) {
			frame[0][0] = image->at<uchar>(y - 1, x - 1) * Gx[0][0];
			frame[0][1] = image->at<uchar>(y - 1, x) * Gx[0][1];
			frame[0][2] = image->at<uchar>(y - 1, x + 1) * Gx[0][2];
			frame[1][0] = image->at<uchar>(y, x - 1) * Gx[1][0];
			frame[1][1] = image->at<uchar>(y, x) * Gx[1][1];
			frame[1][2] = image->at<uchar>(y, x + 1) * Gx[1][2];
			frame[2][0] = image->at<uchar>(y + 1, x - 1) * Gx[2][0];
			frame[2][1] = image->at<uchar>(y + 1, x) * Gx[2][1];
			frame[2][2] = image->at<uchar>(y + 1, x + 1) * Gx[2][2];
			int newValue = frame[0][0] + frame[0][1] + frame[0][2]
				+ frame[1][0] + frame[1][1] + frame[1][2]
				+ frame[2][0] + frame[2][1] + frame[2][2];
			img_h[(y - 1) * (cols - 2) + x - 1] = newValue;
		}
	}
}

//Process Y - Pasa el filtro en vertical
void Sobel::ProcessY()
{
	int frame[3][3];

	for (int y = 1; y < rows - 1; y++) {
		for (int x = 1; x < cols - 1; x++) {
			frame[0][0] = image->at<uchar>(y - 1, x - 1) * Gy[0][0];
			frame[0][1] = image->at<uchar>(y - 1, x) * Gy[0][1];
			frame[0][2] = image->at<uchar>(y - 1, x + 1) * Gy[0][2];
			frame[1][0] = image->at<uchar>(y, x - 1) * Gy[1][0];
			frame[1][1] = image->at<uchar>(y, x) * Gy[1][1];
			frame[1][2] = image->at<uchar>(y, x + 1) * Gy[1][2];
			frame[2][0] = image->at<uchar>(y + 1, x - 1) * Gy[2][0];
			frame[2][1] = image->at<uchar>(y + 1, x) * Gy[2][1];
			frame[2][2] = image->at<uchar>(y + 1, x + 1) * Gy[2][2];
			int newValue = frame[0][0] + frame[0][1] + frame[0][2] + frame[1][0] + frame[1][1] + frame[1][2] + frame[2][0] + frame[2][1] + frame[2][2];
			img_v[(y-1) * (cols-2) + x - 1] = newValue;
		}
	}
}

//Process Total - Calcula la magnitud del borde
void Sobel::ProcessT()
{
	for (int y = 0; y < rows - 2; y++) {
		for (int x = 0; x < cols - 2; x++) {
			int h = pow(img_h[y * (cols - 2) + x], 2);
			int v = pow(img_v[y * (cols - 2) + x], 2);
			img_t[y * (cols - 2) + x] = sqrt(h + v);
			if (img_t[y * (cols - 2) + x] > max) max = img_t[y * (cols - 2) + x];
			if (img_t[y * (cols - 2) + x] < min) min = img_t[y * (cols - 2) + x];
		}
	}
	free(img_h);
	free(img_v);
}

//Process Final - Normaliza los resultados de magnitud
void Sobel::ProcessF()
{
	double diff = max - min;

	for (int y = 0; y < rows - 2; y++) {
		for (int x = 0; x < cols - 2; x++) {
			double abc = (img_t[y * (cols - 2) + x] - min) / (diff * 1.0);
			img_f[y * (cols - 2) + x] = abc * 255;
		}
	}
	free(img_t);
}

//Write Image - Guarda la imagen en el Mat de salida
void Sobel::WriteImg()
{

	for (int y = 0; y < rows-2; y++) {
		for (int x = 0; x < cols-2; x++) {
			imageOut->at<uchar>(y, x) = img_f[y * (cols - 2) + x];
		}
	}
	free(img_f);
}