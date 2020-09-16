// FiltroSobel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "Sobel.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cout << " Usage: " << argv[0] << " Input_Image Output_Image" << endl;
        return -1;
    }
    Mat image;
    image = imread(argv[1], IMREAD_GRAYSCALE); // Lee el archivo
    if (image.empty()) // Comprobar que el archivo sea correcto
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    //Realizar el proceso de filtro Sobel
    Sobel *sobel = new Sobel(&image);
    sobel->ProcessX();
    sobel->ProcessY();
    sobel->ProcessT();
    sobel->ProcessF();
    sobel->WriteImg();

    //namedWindow("Display window", WINDOW_AUTOSIZE); // Crea una ventana para ver la imagen
    //imshow("Display window", *sobel->imageOut); // Mostrar la imagen en la ventana

    imwrite(argv[2], *sobel->imageOut);
    waitKey(0); // Esperar tecla para salir
    return 0;
}