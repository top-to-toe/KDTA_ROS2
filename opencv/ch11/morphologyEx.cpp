#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/hansollee/Documents/KDTA_ROS2/opencv/data/";

int main() {
    Mat img = imread(folder + "milkdrop.bmp");
    Mat bin;
    threshold(img, bin, 120, 255, THRESH_BINARY);

    Mat dst1, dst2, dst3, dst4, dst5, dst6;
    // morphologyEx(bin, dst1, MORPH_OPEN, Mat(), Point(), 3);      // 3번 반복
    morphologyEx(bin, dst1, MORPH_OPEN, Mat());
    morphologyEx(bin, dst2, MORPH_CLOSE, Mat());
    morphologyEx(bin, dst3, MORPH_GRADIENT, Mat());
    morphologyEx(bin, dst4, MORPH_TOPHAT, Mat());
    morphologyEx(bin, dst5, MORPH_BLACKHAT, Mat());

    imshow("img", img);
    imshow("bin", bin);
    imshow("dst1(MORPH_OPEN)", dst1);
    imshow("dst2(MORPH_CLOSE)", dst2);
    imshow("dst3(MORPH_GRADIENT)", dst3);
    imshow("dst4(MORPH_TOPHAT)", dst4);
    imshow("dst5(MORPH_BLACKHAT)", dst5);
    waitKey(0);
    return 0;
}