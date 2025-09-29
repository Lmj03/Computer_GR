//#include <iostream>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <stdlib.h>
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid Keyboard(unsigned char key, int x, int y);
//
//struct REctangle {
//    float x1, y1, x2, y2;
//    float r, g, b;
//};
//
//void TimerFunction(int value)
//{
//    glutTimerFunc(100, TimerFunction, 1);
//}
//
//void Draw_Shape(REctangle rect)
//{
//    glColor3f(rect.r, rect.g, rect.b);
//    glRectf(rect.x1, rect.y1, rect.x2, rect.y2);
//}
//
//REctangle rect[30];
//int rectCount = 0;
//int Amount = 0;
//
//bool dragging = false;
//int selectedIndex = -1;
//float prevMouseX, prevMouseY;
//
//// --- 마우스가 사각형 안에 있는지 체크 ---
//bool isInsideRect(REctangle r, float x, float y)
//{
//    float minX = std::min(r.x1, r.x2);
//    float maxX = std::max(r.x1, r.x2);
//    float minY = std::min(r.y1, r.y2);
//    float maxY = std::max(r.y1, r.y2);
//
//    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
//}
//
//// --- 두 사각형이 겹치는지 체크 ---
//bool isOverlap(REctangle a, REctangle b)
//{
//    return !(a.x2 < b.x1 || a.x1 > b.x2 || a.y2 > b.y1 || a.y1 < b.y2);
//}
//
//// --- 두 사각형을 감싸는 bounding box 생성 ---
//REctangle mergeRect(REctangle a, REctangle b)
//{
//    REctangle result;
//    result.x1 = std::min(a.x1, b.x1);
//    result.y1 = std::max(a.y1, b.y1);
//    result.x2 = std::max(a.x2, b.x2);
//    result.y2 = std::min(a.y2, b.y2);
//
//    result.r = (float)rand() / RAND_MAX;
//    result.g = (float)rand() / RAND_MAX;
//    result.b = (float)rand() / RAND_MAX;
//    return result;
//}
//
//void Mouse(int button, int state, int x, int y)
//{
//    float nx = (float)x / 400.0f - 1.0f;
//    float ny = 1.0f - (float)y / 300.0f;
//
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//    {
//        // 클릭한 사각형 찾기
//        for (int i = 0; i < Amount; i++)
//        {
//            if (isInsideRect(rect[i], nx, ny))
//            {
//                selectedIndex = i;
//                dragging = true;
//                prevMouseX = nx;
//                prevMouseY = ny;
//                break;
//            }
//        }
//    }
//    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
//    {
//        dragging = false;
//
//        if (selectedIndex != -1)
//        {
//            // 선택한 사각형과 겹치는 다른 사각형 찾기
//            for (int j = 0; j < Amount; j++)
//            {
//                if (j != selectedIndex && isOverlap(rect[selectedIndex], rect[j]))
//                {
//                    // 새 사각형 생성
//                    rect[selectedIndex] = mergeRect(rect[selectedIndex], rect[j]);
//
//                    // rect[j] 제거 (뒤에서 앞으로 당김)
//                    for (int k = j; k < Amount - 1; k++)
//                        rect[k] = rect[k + 1];
//                    Amount--;
//                    rectCount--;
//                    break;
//                }
//            }
//        }
//        selectedIndex = -1;
//    }
//    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//    {
//        // 우클릭한 사각형 찾기
//        for (int i = 0; i < Amount; i++)
//        {
//            if (isInsideRect(rect[i], nx, ny))
//            {
//                REctangle old = rect[i];
//
//                // 기존 사각형 삭제
//                for (int j = i; j < Amount - 1; j++)
//                    rect[j] = rect[j + 1];
//                Amount--;
//                rectCount--;
//
//                if (rectCount <= 28) // 두 개 추가할 자리 있어야 함
//                {
//                    float width = fabs(old.x2 - old.x1);
//                    float height = fabs(old.y1 - old.y2);
//
//                    // 첫 번째 분리 사각형
//                    rect[Amount].x1 = old.x1;
//                    rect[Amount].y1 = old.y1;
//                    rect[Amount].x2 = old.x1 + width * 0.5f;
//                    rect[Amount].y2 = old.y2 + height * 0.5f;
//                    rect[Amount].r = (float)rand() / RAND_MAX;
//                    rect[Amount].g = (float)rand() / RAND_MAX;
//                    rect[Amount].b = (float)rand() / RAND_MAX;
//                    Amount++;
//                    rectCount++;
//
//                    // 두 번째 분리 사각형
//                    rect[Amount].x1 = old.x1 + width * 0.5f;
//                    rect[Amount].y1 = old.y1 - height * 0.5f;
//                    rect[Amount].x2 = old.x2;
//                    rect[Amount].y2 = old.y2;
//                    rect[Amount].r = (float)rand() / RAND_MAX;
//                    rect[Amount].g = (float)rand() / RAND_MAX;
//                    rect[Amount].b = (float)rand() / RAND_MAX;
//                    Amount++;
//                    rectCount++;
//                }
//                break; // 한 번만 분리
//            }
//        }
//    }
//    glutPostRedisplay();
//}
//
//void Motion(int x, int y)
//{
//    if (dragging && selectedIndex != -1)
//    {
//        float nx = (float)x / 400.0f - 1.0f;
//        float ny = 1.0f - (float)y / 300.0f;
//
//        float dx = nx - prevMouseX;
//        float dy = ny - prevMouseY;
//
//        rect[selectedIndex].x1 += dx;
//        rect[selectedIndex].x2 += dx;
//        rect[selectedIndex].y1 += dy;
//        rect[selectedIndex].y2 += dy;
//
//        prevMouseX = nx;
//        prevMouseY = ny;
//
//        glutPostRedisplay();
//    }
//}
//
//void main(int argc, char** argv)
//{
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
//    glutTimerFunc(100, TimerFunction, 1);
//    glutMainLoop();
//}
//
//GLvoid drawScene()
//{
//    glClearColor(0, 0, 0, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    for (int i = 0; i < Amount; i++)
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
//    case 'a':
//        if (rectCount == 10 ) break;
//        else
//        {
//            rect[rectCount].x1 = (float)(rand() % 800) / 400.0f - 1.0f;
//            rect[rectCount].y1 = 1.0f - (float)(rand() % 600) / 300.0f;
//            rect[rectCount].x2 = rect[rectCount].x1 + (float)(rand() % 200) / 400.0f;
//            rect[rectCount].y2 = rect[rectCount].y1 - (float)(rand() % 150) / 300.0f;
//            rect[rectCount].r = (float)rand() / RAND_MAX;
//            rect[rectCount].g = (float)rand() / RAND_MAX;
//            rect[rectCount].b = (float)rand() / RAND_MAX;
//            rectCount++;
//            Amount++;
//        }
//    }
//    glutPostRedisplay();
//}
