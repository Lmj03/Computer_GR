//#include <iostream>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <stdlib.h>
//#include <time.h>
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid Keyboard(unsigned char key, int x, int y);
//
//bool on1 = false, on2 = false, on3 = false, on4 = false, on5 = false;
//
//struct Position {
//    float x, y;
//};
//
//struct REctangle
//{
//    float x1, y1, x2, y2;
//    float r, g, b;
//    float middlex, middley;
//    float dx, dy;   // 이동 속도
//    float originalX, originalY; // 처음 생성된 위치
//};
//
//REctangle rect[5];
//int Shape_Count = 0;
//
//int frameCounter = 0; // 지그재그 전환용 카운터
//int leaderIndex = -1; // 리더 사각형 인덱스
//const int TRAIL_LENGTH = 50; // 궤적 길이
//Position trail[50]; // 리더의 중심 위치 궤적
//int trailIndex = 0; // 현재 궤적 인덱스
//
//void TimerFunction(int value)
//{
//    if (on1)
//    {
//        for (int i = 0; i < Shape_Count; i++)
//        {
//            rect[i].x1 += rect[i].dx;
//            rect[i].x2 += rect[i].dx;
//            rect[i].y1 += rect[i].dy;
//            rect[i].y2 += rect[i].dy;
//
//            if (rect[i].x1 < -1.0f || rect[i].x2 > 1.0f) rect[i].dx *= -1;
//            if (rect[i].y1 < -1.0f || rect[i].y2 > 1.0f) rect[i].dy *= -1;
//        }
//        glutPostRedisplay();
//    }
//
//    if (on2)
//    {
//        frameCounter++;
//        for (int i = 0; i < Shape_Count; i++)
//        {
//            // 이동
//            rect[i].x1 += rect[i].dx;
//            rect[i].x2 += rect[i].dx;
//            rect[i].y1 += rect[i].dy;
//            rect[i].y2 += rect[i].dy;
//
//            // 벽 충돌
//            if (rect[i].x1 < -1.0f || rect[i].x2 > 1.0f) rect[i].dx *= -1;
//            if (rect[i].y1 < -1.0f || rect[i].y2 > 1.0f) rect[i].dy *= -1;
//
//            // 일정 주기마다 y 방향 반전 → 지그재그
//            if (frameCounter % 30 == 0) { // 30프레임마다 반전 (약 0.5초)
//                rect[i].dy *= -1;
//            }
//        }
//        glutPostRedisplay();
//    }
//
//    if (on3)
//    {
//        for (int i = 0; i < Shape_Count; i++)
//        {
//            rect[i].x1 = rect[i].middlex - ((float)rand() / RAND_MAX) * 0.3f;
//            rect[i].y1 = rect[i].middley - ((float)rand() / RAND_MAX) * 0.3f;
//            rect[i].x2 = rect[i].middlex + ((float)rand() / RAND_MAX) * 0.3f;
//            rect[i].y2 = rect[i].middley + ((float)rand() / RAND_MAX) * 0.3f;
//        }
//        glutPostRedisplay();
//    }
//
//    if (on4)
//    {
//        for (int i = 0; i < Shape_Count; i++)
//        {
//            rect[i].r = (float)rand() / RAND_MAX;
//            rect[i].g = (float)rand() / RAND_MAX;
//            rect[i].b = (float)rand() / RAND_MAX;
//        }
//        glutPostRedisplay();
//    }
//
//    if (on5 && leaderIndex != -1) // 꼬리 물고 따라하기
//    {
//        // 리더의 새로운 이동값 생성
//        float leaderDx = ((float)rand() / RAND_MAX - 0.5f) * 0.02f;
//        float leaderDy = ((float)rand() / RAND_MAX - 0.5f) * 0.02f;
//
//        // 리더 이동
//        rect[leaderIndex].x1 += leaderDx;
//        rect[leaderIndex].y1 += leaderDy;
//        rect[leaderIndex].x2 += leaderDx;
//        rect[leaderIndex].y2 += leaderDy;
//
//        // 벽 충돌 체크
//        if (rect[leaderIndex].x1 < -1.0f || rect[leaderIndex].x2 > 1.0f) {
//            leaderDx *= -1;
//            rect[leaderIndex].x1 += leaderDx;
//            rect[leaderIndex].x2 += leaderDx;
//        }
//        if (rect[leaderIndex].y1 < -1.0f || rect[leaderIndex].y2 > 1.0f) {
//            leaderDy *= -1;
//            rect[leaderIndex].y1 += leaderDy;
//            rect[leaderIndex].y2 += leaderDy;
//        }
//
//        // 리더의 중심 위치를 궤적에 저장
//        float centerX = (rect[leaderIndex].x1 + rect[leaderIndex].x2) / 2.0f;
//        float centerY = (rect[leaderIndex].y1 + rect[leaderIndex].y2) / 2.0f;
//
//        trail[trailIndex] = { centerX, centerY };
//        trailIndex = (trailIndex + 1) % TRAIL_LENGTH;
//
//        // 다른 사각형들이 궤적을 따라 이동
//        int followOrder = 1;
//        for (int i = 0; i < Shape_Count; i++) {
//            if (i == leaderIndex) continue;
//
//            // 각 사각형의 따라갈 거리 계산 (간격을 두고 따라감)
//            int followDistance = followOrder * 8; // 8프레임 간격으로 따라감
//
//            // 궤적에서 따라갈 위치 계산
//            int followTrailIndex = (trailIndex - followDistance + TRAIL_LENGTH) % TRAIL_LENGTH;
//
//            if (followDistance < TRAIL_LENGTH) {
//                Position targetPos = trail[followTrailIndex];
//
//                // 목표 위치로 사각형 이동 (중심을 맞춤)
//                float currentCenterX = (rect[i].x1 + rect[i].x2) / 2.0f;
//                float currentCenterY = (rect[i].y1 + rect[i].y2) / 2.0f;
//
//                float moveX = targetPos.x - currentCenterX;
//                float moveY = targetPos.y - currentCenterY;
//
//                rect[i].x1 += moveX;
//                rect[i].y1 += moveY;
//                rect[i].x2 += moveX;
//                rect[i].y2 += moveY;
//
//                // 벽 경계 체크 (벗어나지 않도록)
//                if (rect[i].x1 < -1.0f) {
//                    rect[i].x1 = -1.0f;
//                    rect[i].x2 = rect[i].x1 + 0.2f;
//                }
//                if (rect[i].x2 > 1.0f) {
//                    rect[i].x2 = 1.0f;
//                    rect[i].x1 = rect[i].x2 - 0.2f;
//                }
//                if (rect[i].y1 < -1.0f) {
//                    rect[i].y1 = -1.0f;
//                    rect[i].y2 = rect[i].y1 + 0.2f;
//                }
//                if (rect[i].y2 > 1.0f) {
//                    rect[i].y2 = 1.0f;
//                    rect[i].y1 = rect[i].y2 - 0.2f;
//                }
//            }
//            followOrder++;
//        }
//        glutPostRedisplay();
//    }
//
//    glutTimerFunc(16, TimerFunction, 1);
//}
//
//void Mouse(int button, int state, int x, int y)
//{
//    float nx = (float)x / 400.0f - 1.0f;
//    float ny = 1.0f - (float)y / 300.0f;
//
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//    {
//        if (Shape_Count == 5) return;
//        rect[Shape_Count].middlex = nx;
//        rect[Shape_Count].middley = ny;
//        rect[Shape_Count].originalX = nx; // 처음 생성 위치 저장
//        rect[Shape_Count].originalY = ny;
//        rect[Shape_Count].x1 = nx - 0.1f;
//        rect[Shape_Count].y1 = ny - 0.1f;
//        rect[Shape_Count].x2 = nx + 0.1f;
//        rect[Shape_Count].y2 = ny + 0.1f;
//        rect[Shape_Count].r = (float)rand() / RAND_MAX;
//        rect[Shape_Count].g = (float)rand() / RAND_MAX;
//        rect[Shape_Count].b = (float)rand() / RAND_MAX;
//
//        // 속도 랜덤 지정
//        rect[Shape_Count].dx = ((float)rand() / RAND_MAX - 0.5f) * 0.02f;
//        rect[Shape_Count].dy = ((float)rand() / RAND_MAX - 0.5f) * 0.02f;
//        if (rect[Shape_Count].dx == 0) rect[Shape_Count].dx = 0.01f;
//        if (rect[Shape_Count].dy == 0) rect[Shape_Count].dy = 0.01f;
//
//        Shape_Count++;
//    }
//    glutPostRedisplay();
//}
//
//void Motion(int x, int y) {}
//
//void Draw_Shape(REctangle rect)
//{
//    glColor3f(rect.r, rect.g, rect.b);
//    glRectf(rect.x1, rect.y1, rect.x2, rect.y2);
//}
//
//void main(int argc, char** argv)
//{
//    srand((unsigned int)time(NULL));
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(0, 0);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Example1");
//
//    glewExperimental = GL_TRUE;
//    if (glewInit() != GLEW_OK)
//    {
//        std::cerr << "Unable to initialize GLEW" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//
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
//    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//    for (int i = 0; i < Shape_Count; i++)
//        Draw_Shape(rect[i]);
//
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
//        Shape_Count = 0;
//        leaderIndex = -1;
//        trailIndex = 0;
//        // 궤적 기록 초기화
//        for (int i = 0; i < TRAIL_LENGTH; i++) {
//            trail[i] = { 0, 0 };
//        }
//        break;
//    case '1':
//        on1 = !on1;
//        break;
//    case '2':
//        on2 = !on2;
//        frameCounter = 0; // 시작할 때 리셋
//        break;
//    case '3':
//        on3 = !on3;
//        break;
//    case '4':
//        on4 = !on4;
//        break;
//    case '5':
//        if (Shape_Count > 0) {
//            leaderIndex = rand() % Shape_Count; // 리더 랜덤 선택
//            on5 = !on5;
//            trailIndex = 0;
//
//            // 궤적 기록 초기화
//            for (int i = 0; i < TRAIL_LENGTH; i++) {
//                trail[i] = { 0, 0 };
//            }
//
//            // 리더의 현재 위치로 궤적 초기화
//            if (on5) {
//                float centerX = (rect[leaderIndex].x1 + rect[leaderIndex].x2) / 2.0f;
//                float centerY = (rect[leaderIndex].y1 + rect[leaderIndex].y2) / 2.0f;
//                for (int i = 0; i < TRAIL_LENGTH; i++) {
//                    trail[i] = { centerX, centerY };
//                }
//            }
//        }
//        break;
//    case 'm':
//        // 모든 사각형을 처음 생성된 위치로 이동 (현재 크기 유지)
//        for (int i = 0; i < Shape_Count; i++) {
//            // 현재 크기 계산
//            float currentWidth = rect[i].x2 - rect[i].x1;
//            float currentHeight = rect[i].y2 - rect[i].y1;
//
//            // 원래 위치를 중심으로 현재 크기로 설정
//            rect[i].x1 = rect[i].originalX - currentWidth / 2.0f;
//            rect[i].y1 = rect[i].originalY - currentHeight / 2.0f;
//            rect[i].x2 = rect[i].originalX + currentWidth / 2.0f;
//            rect[i].y2 = rect[i].originalY + currentHeight / 2.0f;
//        }
//        break;
//    case's':
//		on1 = on2 = on3 = on4 = on5 = false;
//        break;
//    }
//    glutPostRedisplay();
//}