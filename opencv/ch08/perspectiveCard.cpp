#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void *data);                                                         // 콜백함수

String folder = "/home/hansollee/Documents/KDTA_ROS2/opencv/data/";
Mat src;
bool flag = false;
Point2f srcPts[4], dstPts[4];

int main() {
    Mat img = imread(folder + "card.bmp");

    namedWindow("src");
    setMouseCallback("src", onMouse);

    imshow("src", src);
    waitKey(0);
    destroyAllWindows();
    return 0;
}

void onMouse(int event, int x, int y, int flags, void *data) {
    static int cnt = 0;
    switch (event) {
        case EVENT_LBUTTONDOWN:
            if(cnt < 4) {
                srcPts[cnt++] = Point2f(x, y);
            }
            cout << "mouse left button down\n" << "x: " << x << ", y: " << y << endl;
            ptr->ptOld = Point(x, y);
            ptr->flag = true;
            break;
        case EVENT_LBUTTONUP:
            cout << "mouse left button up\n" << "x: " << x << ", y: " << y << endl;
            ptr->flag = false;
            break;
        case EVENT_MOUSEMOVE:
            if(ptr->flag & EVENT_FLAG_LBUTTON) {
                line(ptr->img, ptr->ptOld, Point(x, y), ptr->blue, 3);
                imshow("img", ptr->img);
                ptr->ptOld = Point(x, y);
            }
    }
}