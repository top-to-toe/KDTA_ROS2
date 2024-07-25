#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 이미지 파일이 저장된 폴더 경로
String folder = "/home/hansollee/Documents/KDTA_ROS2/opencv/data/";

// 사각형의 초기 위치 및 크기
int rect_x = 100;
int rect_y = 100;
int rect_width = 50;
int rect_height = 50;

// 사용할 데이터 구조체 정의
struct Mydata {
    Point ptOld;  // 이전 마우스 위치
    Point ptNew;  // 현재 마우스 위치
    Mat img;      // 이미지 데이터
    Scalar black = Scalar(0, 0, 0);    // 색상 정의
    Scalar white = Scalar(255, 255, 255);
    Scalar yellow = Scalar(0, 255, 255);
    Scalar blue = Scalar(255, 0, 0);
    Scalar green = Scalar(0, 255, 0);
    Scalar red = Scalar(0, 0, 255);
    bool flag = false;  // 마우스 버튼 눌림 상태
    vector<Vec3b> rgbValues;  // 클릭한 픽셀의 RGB 값 저장
};

// 마우스 이벤트 핸들러 함수 정의
void onMouse(int event, int x, int y, int flags, void *data);

int main() {
    // 데이터 구조체 인스턴스 생성
    Mydata mydata;
    // 이미지 파일 읽기
    mydata.img = imread(folder + "lenna.bmp");

    // 이미지 파일 읽기 실패 시 처리
    if (mydata.img.empty()) {
        cerr << "Error: Image not found!" << endl;
        return -1;
    }

    // 윈도우 생성 및 마우스 이벤트 콜백 함수 설정
    namedWindow("img");
    setMouseCallback("img", onMouse, (void *)&mydata);

    // 메인 루프
    while (true) {
        // 이미지 복사본 생성
        Mat img_display = mydata.img.clone();

        // 현재 사각형 그리기
        rectangle(img_display, Point(rect_x, rect_y), Point(rect_x + rect_width, rect_y + rect_height), mydata.black, 2);

        // 이미지 출력
        imshow("img", img_display);

        // ESC 키 입력 시 종료
        if (waitKey(10) == 27) {  
            // JSON 파일로 RGB 값 저장
            FileStorage fs(folder + "mouseRGBvector.json", FileStorage::WRITE);
            fs << "RGB_Values" << "[";
            for (const auto& rgb : mydata.rgbValues) {
                fs << "{" << "R" << (int)rgb[2] << "G" << (int)rgb[1] << "B" << (int)rgb[0] << "}";
            }
            fs << "]";
            fs.release();

            break;  // 루프 종료
        }
    }

    return 0;  // 프로그램 종료
}

// 마우스 이벤트 핸들러 함수 구현
void onMouse(int event, int x, int y, int flags, void *data) {
    // 데이터 구조체 포인터로 변환
    Mydata *ptr = (Mydata *)data;
    
    switch (event) {
        case EVENT_MOUSEMOVE:
            // 마우스 이동 시 사각형 위치 업데이트
            rect_x = x;
            rect_y = y;
            break;
        case EVENT_LBUTTONDOWN:
            cout << "Mouse left button down" << endl;
            // 왼쪽 마우스 버튼 클릭 시 처리
            if (x >= 0 && x < ptr->img.cols && y >= 0 && y < ptr->img.rows) {
                // 클릭한 픽셀의 RGB 값 추출
                Vec3b intensity = ptr->img.at<Vec3b>(y, x);
                cout << "RGB values at (x=" << x << ", y=" << y << "): "
                     << "R=" << (int)intensity[2] << ", "
                     << "G=" << (int)intensity[1] << ", "
                     << "B=" << (int)intensity[0] << endl;

                // RGB 값을 벡터에 저장
                ptr->rgbValues.push_back(intensity);
            }
            ptr->flag = true;  // 마우스 버튼 눌림 상태 설정
            break;
        case EVENT_LBUTTONUP:
            cout << "Mouse left button up" << endl;
            ptr->flag = false;  // 마우스 버튼 눌림 상태 해제
            break;
    }
}

/*
    1. 마우스 이벤트 핸들러 함수 (onMouse):
        onMouse 함수는 마우스 동작을 감지하고 처리하는 역할을 합니다.
        event: 발생한 마우스 이벤트를 나타내는 변수입니다.
        x, y: 마우스 클릭 또는 이동 시의 좌표입니다.
        flags: 마우스 이벤트에 대한 추가 정보입니다.
        data: 사용자 데이터(여기서는 Mydata 구조체)에 대한 포인터입니다.

    2.마우스 이벤트 처리:
        EVENT_MOUSEMOVE: 마우스가 움직일 때 사각형의 위치를 마우스 위치로 업데이트합니다.
        EVENT_LBUTTONDOWN: 왼쪽 마우스 버튼을 클릭했을 때 처리합니다.
            픽셀 좌표가 유효한 범위 내에 있으면 해당 좌표의 RGB 값을 추출하여 출력합니다.
            추출한 RGB 값을 rgbValues 벡터에 저장합니다.
            flag를 true로 설정하여 마우스 버튼이 눌린 상태임을 나타냅니다.
        EVENT_LBUTTONUP: 왼쪽 마우스 버튼을 뗐을 때 처리합니다.
            flag를 false로 설정하여 마우스 버튼이 눌리지 않은 상태임을 나타냅니다.

  
*/

/* 과제 내용 */
// 1. lenna 이미지 window 출력
// 2. 마우스 따라다니는 사각형(size: [50, 50])
// 3. 마우스 클릭시 마우스 위치의 RGB 값을 cout -> 터미널 화면에 출력
// 4. RGB vector에 넣고 FileStorage 저장 "mouseRGBvector.json"
// *5. 최적화 tickmeter(미구현)