# KDTA ROS2

- 공유 슬라이드 [링크](https://docs.google.com/presentation/d/1453nx14DVMk0nBLW7jpt0g6x7a7z2wuNaJKmcVQi4rw/edit?usp=sharing)

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
  - github 연동 (git clone [URL])
  - opencv 환경 설정 (sudo apt install libopencv-dev python3-opencv, sudo apt update, sudo apt upgrade)

- 3차시
  - cmake, make 설치 및 컴파일 용도 사용 (sudo apt cmake, sudo apt make)
  - CMakeLists.txt 및 c_cpp_properties.json 작성 (환경설정 관련)
  - imread 및 imshow, namedWindow 등 활용하여 간단한 출력화면 구성(first / helloworld.cpp, ch02 / windows.cpp & .. / movewindows.cpp)
  - Point, Size, Rect 키워드 활용 및 멤버 자료 활용하여 출력 예제 화면 크기 등 변경 실행
---
## 2024-07-24
---
- matrix 연산자 사용 예시 구현(matOp1 ~ matOp4)
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
- matrix 연산자 멤버 자료(Clone, setTo)를 활용한 복제(matOp2.cpp)
- ROI(Region of Interest - 이미지 내 관심영역)을 활용한 이미지 내 특정 영역 추출 및 출력(matOp3.cpp) - Rect 클래스 변수 활용(특정 초기 입력 좌표값을 통한 관심영역 지정)
- (matOp4.cpp)