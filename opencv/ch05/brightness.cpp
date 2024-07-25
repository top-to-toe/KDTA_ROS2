#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/hansollee/Documents/KDTA_ROS2/opencv/data/";

int main() {
    Scalar white = Scalar(255, 255, 255);
    Scalar yellow = Scalar(0, 255, 255);
    Scalar blue = Scalar(255, 0, 0);
    Scalar green = Scalar(0, 255, 0);
    Scalar red = Scalar(0, 0, 255);
    Mat img = imread(folder + "lenna.bmp", IMREAD_COLOR);
    Mat imgGray = imread(folder + "lenna.bmp", IMREAD_GRAYSCALE);

    Mat imgcvtgray;
    cvtColor(img, imgcvtgray, COLOR_BGR2GRAY);
    Mat imgAdd = imgGray + 50;
    Mat imgAddcenter = imgGray + (imgGray - 125) * 1.0;

    imshow("img", img);
    imshow("imgGray", imgGray);
    imshow("imgcvtgray", imgcvtgray);
    imshow("imgAdd", imgAdd);
    imshow("imgAddcenter", imgAddcenter);

    waitKey(0);
    return 0;
}