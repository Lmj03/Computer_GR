//#include <iostream>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <stdlib.h>
//#include <time.h>
//#include <vector>
//#include <cmath>
//using namespace std;
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid Keyboard(unsigned char key, int x, int y);
//
//struct REctangle {
//    float x1, y1, x2, y2;
//    float r, g, b;
//    bool clickon;
//    bool fixed; // 올바른 위치에 고정되었는지
//    bool Automove;
//};
//
//REctangle rect[13];
//REctangle randomRect[13]; // 우측 사각형의 위치 저장
//int selectedRect = -1; // 현재 선택된 사각형 인덱스
//float dragOffsetX = 0, dragOffsetY = 0; // 드래그 오프셋
//
//void Draw_Board(REctangle rect)
//{
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glColor3f(rect.r, rect.g, rect.b);
//    glRectf(rect.x1, rect.y1, rect.x2, rect.y2);
//}
//
//void Draw_Shape(REctangle rect, int index)
//{
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//    // 고정된 사각형은 약간 어둡게 표시
//
//    glColor3f(rect.r, rect.g, rect.b);
//
//
//    glRectf(randomRect[index].x1, randomRect[index].y1, randomRect[index].x2, randomRect[index].y2);
//
//}
//
//void Shape_random(REctangle& rect)
//{
//    // 원래 사각형의 크기 계산
//    float width = rect.x2 - rect.x1;
//    float height = rect.y2 - rect.y1;
//
//    // 우측 영역(0 ~ 1)에서 랜덤 위치 생성
//    float new_x1 = (float)rand() / RAND_MAX;  // 0.0 ~ 1.0
//    float new_y1 = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;  // -1.0 ~ 1.0
//
//    // 화면 경계를 벗어나지 않도록 조정
//    if (new_x1 + width > 1.0f) {
//        new_x1 = 1.0f - width;
//    }
//    if (new_y1 + height > 1.0f) {
//        new_y1 = 1.0f - height;
//    }
//    if (new_y1 < -1.0f) {
//        new_y1 = -1.0f;
//    }
//
//    // 새로운 위치로 업데이트 (색상은 유지)
//    rect.x1 = new_x1;
//    rect.y1 = new_y1;
//    rect.x2 = new_x1 + width;
//    rect.y2 = new_y1 + height;
//    rect.fixed = false;
//}
//
//void InitRandomRects()
//{
//    // 프로그램 시작 시 한 번만 랜덤 위치 생성
//    for (int i = 0; i < 13; i++)
//    {
//        randomRect[i] = rect[i]; // 색상 복사
//        randomRect[i].fixed = false;
//        Shape_random(randomRect[i]); // 랜덤 위치 생성
//    }
//}
//
//bool IsInCorrectPosition(int index, float threshold = 0.1f)
//{
//    // 원래 위치(rect[index])와 현재 위치(randomRect[index])의 거리 계산
//    float dx = abs(randomRect[index].x1 - rect[index].x1);
//    float dy = abs(randomRect[index].y1 - rect[index].y1);
//
//    return (dx < threshold && dy < threshold);
//}
//
//void CheckAndFixPosition(int index)
//{
//    if (IsInCorrectPosition(index)) {
//        // 정확한 위치에 스냅
//        randomRect[index].x1 = rect[index].x1;
//        randomRect[index].y1 = rect[index].y1;
//        randomRect[index].x2 = rect[index].x2;
//        randomRect[index].y2 = rect[index].y2;
//        randomRect[index].fixed = true;
//        cout << "rect" << index << " is fixed" << endl;
//        selectedRect = -1; // 선택 해제
//    }
//
//}
//
//void TimerFunction(int value)
//{
//    for (int i = 0; i < 13; i++)
//    {
//        if (!randomRect[i].fixed && randomRect[i].Automove)
//        {
//            float x = rect[i].x1;
//            float y = rect[i].y1;
//            float nx = randomRect[i].x1;
//            float ny = randomRect[i].y1;
//            float dirx = x - nx;
//            float diry = y - ny;
//            float length = sqrt(dirx * dirx + diry + diry);
//            if (length > 0.01f)
//            {
//               
//                randomRect[i].x1 += dirx * 0.1f;
//                randomRect[i].y1 += diry * 0.1f;
//                randomRect[i].x2 += dirx * 0.1f;
//                randomRect[i].y2 += diry * 0.1f;
//            }
//            else
//            {
//                randomRect[i].x1 = rect[i].x1;
//                randomRect[i].y1 = rect[i].y1;
//                randomRect[i].x2 = rect[i].x2;
//                randomRect[i].y2 = rect[i].y2;
//                randomRect[i].fixed = true;
//            }
//        }
//    }
//    glutPostRedisplay();
//    glutTimerFunc(16, TimerFunction, 1);
//}
//
//void Mouse(int button, int state, int x, int y)
//{
//    float nx = (float)x / 600.0f - 1.0f; // 윈도우 크기에 맞게 조정
//    float ny = 1.0f - (float)y / 300.0f;
//
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//    {
//        selectedRect = -1;
//
//        // 우측 사각형들 중에서 클릭된 것 찾기 (고정되지 않은 것만)
//        for (int i = 0; i < 13; i++)
//        {
//            if (randomRect[i].fixed) continue; // 고정된 사각형은 선택 불가
//
//            float minX = min(randomRect[i].x1, randomRect[i].x2);
//            float maxX = max(randomRect[i].x1, randomRect[i].x2);
//            float minY = min(randomRect[i].y1, randomRect[i].y2);
//            float maxY = max(randomRect[i].y1, randomRect[i].y2);
//
//            if (nx >= minX && nx <= maxX && ny >= minY && ny <= maxY)
//            {
//                selectedRect = i;
//                dragOffsetX = nx - randomRect[i].x1;
//                dragOffsetY = ny - randomRect[i].y1;
//                break;
//            }
//        }
//    }
//    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
//    {
//        if (selectedRect != -1) {
//            CheckAndFixPosition(selectedRect);
//        }
//    }
//
//    glutPostRedisplay();
//}
//
//void Motion(int x, int y)
//{
//    if (selectedRect != -1 && !randomRect[selectedRect].fixed)
//    {
//        float nx = (float)x / 600.0f - 1.0f;
//        float ny = 1.0f - (float)y / 300.0f;
//
//        float width = randomRect[selectedRect].x2 - randomRect[selectedRect].x1;
//        float height = randomRect[selectedRect].y2 - randomRect[selectedRect].y1;
//
//        // 새 위치 계산
//        randomRect[selectedRect].x1 = nx - dragOffsetX;
//        randomRect[selectedRect].y1 = ny - dragOffsetY;
//        randomRect[selectedRect].x2 = randomRect[selectedRect].x1 + width;
//        randomRect[selectedRect].y2 = randomRect[selectedRect].y1 + height;
//
//        // 화면 경계 체크
//        if (randomRect[selectedRect].x1 < -1.0f) {
//            randomRect[selectedRect].x1 = -1.0f;
//            randomRect[selectedRect].x2 = randomRect[selectedRect].x1 + width;
//        }
//        if (randomRect[selectedRect].x2 > 1.0f) {
//            randomRect[selectedRect].x2 = 1.0f;
//            randomRect[selectedRect].x1 = randomRect[selectedRect].x2 - width;
//        }
//        if (randomRect[selectedRect].y1 < -1.0f) {
//            randomRect[selectedRect].y1 = -1.0f;
//            randomRect[selectedRect].y2 = randomRect[selectedRect].y1 + height;
//        }
//        if (randomRect[selectedRect].y2 > 1.0f) {
//            randomRect[selectedRect].y2 = 1.0f;
//            randomRect[selectedRect].y1 = randomRect[selectedRect].y2 - height;
//        }
//
//        glutPostRedisplay();
//    }
//}
//
//void main(int argc, char** argv)
//{
//    srand((unsigned int)time(NULL));
//    rect[0] = { -0.95f, 0.4f, -0.8f, 0.8f, 1.0f, 0.0f, 0.0f, false, false, false }; // 빨강
//    rect[1] = { -0.95f, 0.0f, -0.8f, 0.3f, 0.0f, 1.0f, 0.0f, false, false, false }; // 초록
//    rect[2] = { -0.8f, -0.2f, -0.6f, 0.6f, 0.0f, 0.0f, 1.0f, false, false, false }; // 파랑
//    rect[3] = { -0.6f, 0.0f, -0.2f, 0.4f, 1.0f, 1.0f, 0.0f, false, false, false }; // 노랑
//    rect[4] = { -0.2f, 0.0f, -0.05f, 0.4f, 1.0f, 0.0f, 1.0f, false, false, false }; // 보라
//    rect[5] = { -0.6f, -0.6f, -0.2f, -0.2f, 0.0f, 1.0f, 1.0f, false, false, false }; // 하늘
//    rect[6] = { -0.91f, -0.6f, -0.6f, -0.2f, 0.5f, 0.5f, 0.5f, false, false, false }; // 회색
//    rect[7] = { -0.5f, 0.6f, -0.2f, 0.9f, 1.0f, 0.5f, 0.0f, false, false, false }; // 주황
//    rect[8] = { -0.2f, -0.8f, -0.07f, -0.2f, 0.5f, 0.0f, 0.5f, false, false, false }; // 자주
//    rect[9] = { -0.75f, 0.6f, -0.5f, 1.0f, 0.0f, 0.5f, 0.5f, false, false , false }; // 청록
//    rect[10] = { -0.3f, -0.1f, -0.1f, 0.0f, 0.5f, 0.5f, 0.0f, false, false, false }; // 올리브
//    rect[11] = { -0.4f, -0.6f, -0.3f, -0.8f, 0.25f, 0.75f, 0.5f, false, false, false }; // 연두
//    rect[12] = { -0.8f, -0.6f, -0.5f, -0.8f, 0.75f, 0.5f, 0.25f, false, false, false }; // 살구
//
//    // 프로그램 시작 시 랜덤 위치 초기화
//    InitRandomRects();
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(0, 0);
//    glutInitWindowSize(1200, 600);
//    glutCreateWindow("Puzzle Game");
//    glewExperimental = GL_TRUE;
//    if (glewInit() != GLEW_OK
//    {
//        std::cerr << "Unable to initialize GLEW" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutKeyboardFunc(Keyboard);
//    glutMotionFunc(Motion);
//    glutMouseFunc(Mouse);
//    glutTimerFunc(16, TimerFunction, 1);
//    glutMainLoop();
//}
//
//GLvoid drawScene()
//{
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // 중앙 세로선
//    glColor3f(0.0f, 0.0f, 0.0f);
//    glBegin(GL_LINES);
//    glVertex2f(0.0f, -1.0f);
//    glVertex2f(0.0f, 1.0f);
//    glEnd();
//
//    for (int i = 0; i < 13; i++)
//    {
//        Draw_Board(rect[i]);  // 왼쪽에 테두리 (목표 위치)
//        Draw_Shape(rect[i], i);  // 우측의 드래그 가능한 사각형
//    }
//    glutSwapBuffers();
//}
//
//GLvoid Reshape(int w, int h)
//{
//    glViewport(0, 0, w, h);
//}
//
//GLvoid Keyboard(unsigned char key, int x, int y)
//{
//    switch (key) {
//    case 'q':
//        exit(0);
//        break;
//    case 'r':
//    case 'R':
//        InitRandomRects(); // R키로 게임 리셋
//        break;
//    case 'p':
//    case 'P':
//        // 고정되지 않은 도형 중 하나를 자동으로 맞춰주기
//        for (int i = 0; i < 13; i++)
//        {
//            if (!randomRect[i].fixed) // 고정되지 않은 도형 찾기
//            {
//				randomRect[i].Automove = true;
//                
//                break; // 한 개만 맞추고 루프 종료
//            }
//        }
//        break;
//    }
//    glutPostRedisplay();
//}