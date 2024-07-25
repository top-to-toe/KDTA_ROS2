# KDTA ROS2

- 공유 슬라이드 [[링크](https://docs.google.com/presentation/d/1453nx14DVMk0nBLW7jpt0g6x7a7z2wuNaJKmcVQi4rw/edit?usp=sharing)]

---

## 2024-07-23

---
- 1차시
  - VMware 설치
  - ubuntu 22.04 설치
  - terminator 설치 (sudo apt install terminator)
  - git 설치 (sudo apt install git)

- 2차시
  - vscode 설치 (sudo apt install .vs~)
  - github 연동 (git clone [github URL])
  - opencv 환경 설정 (sudo apt install libopencv-dev python3-opencv, sudo apt update, sudo apt upgrade)

- 3차시
  - cmake, make 설치 및 컴파일 용도 사용 (sudo apt cmake, sudo apt make)
  - CMakeLists.txt 및 c_cpp_properties.json 작성 (환경설정 관련)
  - imread 및 imshow, namedWindow 등 활용하여 간단한 출력화면 구성(first / helloworld.cpp, ch02 / windows.cpp & .. / movewindows.cpp)
  - Point, Size, Rect 클래스 멤버 자료 활용하여 출력 예제 화면 크기 등 변경 실행


---

## 2024-07-24

---
- matrix 연산자 사용 예시 구현
  - Fixed Pixel Type: matrix 클래스의 element가 어떤 타입의 데이터인지 지정.
    - CV_8UC1 : 8 - bit unsigned integer : uchar(0..255)
      - 8 : bit 단위로서 8bit를 의미
      - U : unsigend의 약자, ( U : Unsinged, S : Signed, F : Floating )
      - C1 : Channel의 약자이며 1채널을 의미한다. ( 1채널의 경우 C1 을 생략 가능하여 CV_8UC1 = CV_8U 와 같은 값을 지니게 된다. )
    - CV_8SC1 : 8 - bit signed integer : schar(-128..127)
    - CV_16UC1 : 16 - bit unsigned integer : ushort(0..65535)
    - CV_16SC1 : 16 - bit signed integer : short(-32768..32767)
    - CV_32SC1 : 32 - bit signed integer : int(-2147483648..2147483647)
    - CV_32FC1 : 32 - bit floating - point number : float(-FLT_MAX..FLT_MAX, INF, NAN)
    - CV_64FC1 : 64 - bit floating - point number : double(-DBL_MAX..DBL_MAX, INF, NAN)
  - Scalar 멤버함수 속성 활용(색상 출력)
  - matrix 연산자 멤버 객체(Clone, setTo)를 활용한 복제 [[matOp2.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch03/matOp2.cpp)]
  - ROI(Region of Interest: 이미지 내 관심영역)을 활용한 이미지 내 특정 영역 추출 및 출력 / Rect 클래스 변수 활용(특정 초기 입력 좌표값을 통한 관심영역 지정)
    [[matOp3.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch03/matOp3.cpp)]
  - 행렬 조작 기능 학습, 다양한 방법으로 행렬 접근 및 조작 - matrix 클래스(cv::Mat) 정적 멤버 함수 zeros(지정된 크기와 데이터 타입으로 모든 요소를 0으로 초기화하는 역할)사용, 이중 반복문 사용하여 각 픽셀을 반복하면서 해당 픽셀의 값을 1씩 증가('.at<Template>' method를 사용하여 요소에 접근, point 및 iteraotr 각각 활용)
    [[matOp4.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch03/matOp4.cpp)]
  - 외부 저장 공간에 데이터 저장 및 출력 [[matOp5.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch03/matOp5.cpp)]
  - 벡터(Vec3b 사용) 및 스칼라(Scalar) 행렬 객체를 활용한 색상 출력 [[vecOp.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch03/vecOp.cpp)]


- VideoCapture / VideoWriter 클래스 (ch04)
  * 디바이스의 카메라를 통한 비디오 영상 출력 / videoWriter 클래스 객체를 활용하여 동영상 파일 생성 [[video.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch04/video.cpp)]  
    (실습 노트북의 내장 카메라 접근 이슈로 인해 저장된 동영상을 출력)
  * line 그리기 [[line.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch04/line.cpp)]
  * keyboard 조작
    [[keyboard.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch04/keyboard.cpp)]
    [[keyboard2.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch04/keyboard2.cpp)]


---

## 2024-07-25

---
- mouse 기능 동작에 따른 관련 이벤트 표현 [[mouseTest.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch04/mouseTest.cpp)]
- trackBar 조작 기능 구현 [[trackBarTest.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch04/trackBarTest.cpp)] / [[trackBarTest2.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch04/trackBarTest2.cpp)]
- 이미지 합성 [[maskSetTo.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch04/maskSetTo.cpp)]
  - setTo함수로 합성될 이미지에 대해 색상 변경
  - copyTo함수로 합성
  - Masking 되어있는 이미지에 대해 읽어올때(imread()) 속성값으로 인자에 IMREAD_GRAYSCALE를 기재
- file 저장 [[filestorageTest.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch04/filestorageTest.cpp)]
  - FileStorage 클래스 객체의 open함수로 저장될 위치 및 FileStorage::WRITE 속성을 통해 저장에 대해 명시
- 저장된 파일 내용 불러오기 [[fileStorageReadTest.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch04/fileStorageReadTest.cpp)]
  - FileStorage::READ로 저장된 파일을 불러옴에 대해 명시
- chapter 마무리 과제 진행[[chTest.cpp](https://github.com/top-to-toe/KDTA_ROS2/blob/main/opencv/ch04/chTest.cpp)]
  1. TickMeter 객체 사용: TickMeter를 이용하여 tm1과 tm2를 선언하고 시작(tm1.start(), tm2.start()) 및 종료(tm1.stop(), tm2.stop()) 시간을 측정합니다. 이는 FPS 측정과 최적화를 위한 핵심 요소입니다.
  2. 이미지 처리 및 출력: imshow() 함수를 이용하여 img_display 이미지를 출력하고, ESC 키 입력 시 프로그램을 종료합니다. 또한, 현재 마우스 위치에 따라 사각형을 그립니다.
  3. FPS 관리 및 대기 시간 계산: tm1.getFPS()를 이용하여 현재 FPS를 계산하고, 목표 FPS보다 높으면 추가적인 슬립을 통해 CPU 소비를 조정합니다.
  4. 마우스 이벤트 처리: onMouse() 함수를 이용하여 마우스 이벤트를 처리하고, 왼쪽 마우스 클릭 시 클릭한 픽셀의 RGB 값을 출력하고 rgbValues 벡터에 저장합니다.
  5. 파일 저장: 마지막으로, ESC 키 입력 시 rgbValues에 저장된 RGB 값을 JSON 파일로 저장합니다.