#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

String folder = "/home/hansollee/Documents/KDTA_ROS2/opencv/data/";

int rect_x = 100;
int rect_y = 100;
int rect_width = 50;
int rect_height = 50;

struct Mydata {
    Point ptOld;
    Point ptNew;
    Mat img;
    Scalar black = Scalar(0, 0, 0);
    Scalar white = Scalar(255, 255, 255);
    Scalar yellow = Scalar(0, 255, 255);
    Scalar blue = Scalar(255, 0, 0);
    Scalar green = Scalar(0, 255, 0);
    Scalar red = Scalar(0, 0, 255);
    bool flag = false;
    vector<Vec3b> rgbValues; // RGB 값을 저장할 벡터
};

void onMouse(int event, int x, int y, int flags, void *data);

int main() {
    Mydata mydata;
    mydata.img = imread(folder + "lenna.bmp");

    if (mydata.img.empty()) {
        cerr << "Error: Image not found!" << endl;
        return -1;
    }

    namedWindow("img");
    setMouseCallback("img", onMouse, (void *)&mydata);

    while (true) {
        Mat img_display = mydata.img.clone();

        rectangle(img_display, Point(rect_x, rect_y), Point(rect_x + rect_width, rect_y + rect_height), mydata.black, 2);

        imshow("img", img_display);

        if (waitKey(10) == 27) {  
            FileStorage fs(folder + "mouseRGBvector.json", FileStorage::WRITE);
            fs << "RGB_Values" << "[";
            for (const auto& rgb : mydata.rgbValues) {
                fs << "{" << "R" << (int)rgb[2] << "G" << (int)rgb[1] << "B" << (int)rgb[0] << "}";
            }
            fs << "]";
            fs.release();

            break;
        }
    }

    return 0;
}

void onMouse(int event, int x, int y, int flags, void *data) {
    Mydata *ptr = (Mydata *)data;
    
    switch (event) {
        case EVENT_MOUSEMOVE:
            rect_x = x;
            rect_y = y;
            break;
        case EVENT_LBUTTONDOWN:
            cout << "Mouse left button down" << endl;
            if (x >= 0 && x < ptr->img.cols && y >= 0 && y < ptr->img.rows) {
                Vec3b intensity = ptr->img.at<Vec3b>(y, x);
                cout << "RGB values at (x=" << x << ", y=" << y << "): "
                     << "R=" << (int)intensity[2] << ", "
                     << "G=" << (int)intensity[1] << ", "
                     << "B=" << (int)intensity[0] << endl;

                ptr->rgbValues.push_back(intensity);
            }
            ptr->flag = true;
            break;
        case EVENT_LBUTTONUP:
            cout << "Mouse left button up" << endl;
            ptr->flag = false;
            break;
    }
}
