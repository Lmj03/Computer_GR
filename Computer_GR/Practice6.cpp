//#include <iostream>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <stdlib.h>
//#include <time.h>
//#include <vector>
//using namespace std;
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid Keyboard(unsigned char key, int x, int y);
//int ClickCount = 0;
//struct REctangle {
//    float x1, y1, x2, y2; // 좌표
//    float r, g, b;         // 색상
//    float dx, dy;          // 이동 속도
//    int shrinking; // 축소/애니메이션 상태
//};
//
//
//
//
//vector<REctangle> rect;
//void TimerFunction(int value)
//{
//    float shrinkSpeed = 0.002f;
//
//    for (int i = 0; i < rect.size(); )
//    {
//        if (rect[i].shrinking==0)
//        {
//            // 중심 기준 이동
//            float cx = (rect[i].x1 + rect[i].x2) / 2.0f + rect[i].dx;
//            float cy = (rect[i].y1 + rect[i].y2) / 2.0f + rect[i].dy;
//
//            // 반폭/반높이 감소
//            float w = (rect[i].x2 - rect[i].x1) / 2.0f - shrinkSpeed;
//            float h = (rect[i].y2 - rect[i].y1) / 2.0f - shrinkSpeed;
//
//            if (w <= 0.0f || h <= 0.0f)
//            {
//                rect.erase(rect.begin() + i);
//                continue;
//            }
//
//            rect[i].x1 = cx - w;
//            rect[i].x2 = cx + w;
//            rect[i].y1 = cy - h;
//            rect[i].y2 = cy + h;
//        }
//        else if (rect[i].shrinking == 1)
//        {
//			// 중심 기준 이동
//			float cx = (rect[i].x1 + rect[i].x2) / 2.0f + rect[i].dx;
//			float cy = (rect[i].y1 + rect[i].y2) / 2.0f + rect[i].dy;
//			// 반폭/반높이 감소
//			float w = (rect[i].x2 - rect[i].x1) / 2.0f - shrinkSpeed;
//			float h = (rect[i].y2 - rect[i].y1) / 2.0f - shrinkSpeed;
//			if (w <= 0.0f || h <= 0.0f)
//			{
//				rect.erase(rect.begin() + i);
//				continue;
//			}
//			rect[i].x1 = cx - w;
//			rect[i].x2 = cx + w;
//			rect[i].y1 = cy - h;
//			rect[i].y2 = cy + h;
//        }
//        else if (rect[i].shrinking == 2)
//        {
//            // 중심 기준 이동
//            float cx = (rect[i].x1 + rect[i].x2) / 2.0f + rect[i].dx;
//            float cy = (rect[i].y1 + rect[i].y2) / 2.0f + rect[i].dy;
//
//            // 반폭/반높이 감소
//            float w = (rect[i].x2 - rect[i].x1) / 2.0f - shrinkSpeed;
//            float h = (rect[i].y2 - rect[i].y1) / 2.0f - shrinkSpeed;
//
//            if (w <= 0.0f || h <= 0.0f)
//            {
//                rect.erase(rect.begin() + i);
//                continue;
//            }
//
//            rect[i].x1 = cx - w;
//            rect[i].x2 = cx + w;
//            rect[i].y1 = cy - h;
//            rect[i].y2 = cy + h;
//        }
//        else if (rect[i].shrinking == 3)
//        {
//			// 중심 기준 이동
//			float cx = (rect[i].x1 + rect[i].x2) / 2.0f + rect[i].dx;
//			float cy = (rect[i].y1 + rect[i].y2) / 2.0f + rect[i].dy;
//			// 반폭/반높이 감소
//			float w = (rect[i].x2 - rect[i].x1) / 2.0f - shrinkSpeed;
//			float h = (rect[i].y2 - rect[i].y1) / 2.0f - shrinkSpeed;
//			if (w <= 0.0f || h <= 0.0f)
//			{
//				rect.erase(rect.begin() + i);
//				continue;
//			}
//			rect[i].x1 = cx - w;
//			rect[i].x2 = cx + w;
//			rect[i].y1 = cy - h;
//			rect[i].y2 = cy + h;
//        }
//        i++;
//    }
//
//    glutPostRedisplay();
//    glutTimerFunc(16, TimerFunction, 1);
//}
//
//
//
//
//void Draw_Shape(REctangle rect)
//{
//	glColor3f(rect.r, rect.g, rect.b);
//	glRectf(rect.x1, rect.y1, rect.x2, rect.y2);
//}
//
//void Mouse(int button, int state, int x, int y)
//{
//    float nx = (float)x / 400.0f - 1.0f;
//    float ny = 1.0f - (float)y / 300.0f;
//
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//    {
//        for (int i = 0; i < rect.size(); i++)
//        {
//            REctangle r = rect[i];
//            if (nx >= r.x1 && nx <= r.x2 && ny >= r.y1 && ny <= r.y2)
//            {
//                if (ClickCount == 0)
//                {
//                    float cx = (r.x1 + r.x2) / 2.0f;
//                    float cy = (r.y1 + r.y2) / 2.0f;
//
//                    float w = (r.x2 - r.x1) / 2.0f;
//                    float h = (r.y2 - r.y1) / 2.0f;
//
//                    rect.erase(rect.begin() + i);
//
//                    float speed = 0.03f;
//
//                    // 좌/우/상/하 분할
//                    REctangle left = { r.x1, r.y1, cx, r.y2, r.r, r.g, r.b, -speed, 0, 0 };
//                    REctangle right = { cx, r.y1, r.x2, r.y2, r.r, r.g, r.b, speed, 0, 0 };
//                    REctangle top = { r.x1, cy, r.x2, r.y2, r.r, r.g, r.b, 0, speed, 0 };
//                    REctangle down = { r.x1, r.y1, r.x2, cy, r.r, r.g, r.b, 0, -speed, 0 };
//
//                    rect.push_back(left);
//                    rect.push_back(right);
//                    rect.push_back(top);
//                    rect.push_back(down);
//
//                    ClickCount++;
//                    break;
//                }
//                else if (ClickCount == 1)
//                {
//                    float cx = (r.x1 + r.x2) / 2.0f; // 중심점
//                    float cy = (r.y1 + r.y2) / 2.0f;
//
//                    float w = (r.x2 - r.x1) / 2.0f; //폭
//                    float h = (r.y2 - r.y1) / 2.0f; // 높이
//
//                    rect.erase(rect.begin() + i); // 기존 사각형 제거
//
//                    float speed = 0.03f; //날라가는 속도
//
//                    // 대각선 분할
//                    REctangle leftTop = { r.x1, cy, cx, r.y2, r.r, r.g, r.b, -speed, speed, 1 };
//                    REctangle rightTop = { cx, cy, r.x2, r.y2, r.r, r.g, r.b, speed, speed, 1 };
//                    REctangle leftBottom = { r.x1, r.y1, cx, cy, r.r, r.g, r.b, -speed, -speed, 1 };
//                    REctangle rightBottom = { cx, r.y1, r.x2, cy, r.r, r.g, r.b, speed, -speed, 1 };
//
//                    // 벡터에 추가
//                    rect.push_back(leftTop);
//                    rect.push_back(rightTop);
//                    rect.push_back(leftBottom);
//                    rect.push_back(rightBottom);
//
//                    ClickCount++;
//                    break;
//                }
//                else if (ClickCount == 2)
//                {
//                    float cx = (r.x1 + r.x2) / 2.0f;
//                    float cy = (r.y1 + r.y2) / 2.0f;
//
//                    float w = (r.x2 - r.x1) / 2.0f;
//                    float h = (r.y2 - r.y1) / 2.0f;
//
//                    rect.erase(rect.begin() + i);
//
//                    float speed = 0.03f;
//
//                    // 좌/우/상/하 분할
//                    REctangle left = { r.x1, r.y1, cx, r.y2, r.r, r.g, r.b, speed, 0, 0 };
//                    REctangle right = { cx, r.y1, r.x2, r.y2, r.r, r.g, r.b, speed, 0, 0 };
//                    REctangle top = { r.x1, cy, r.x2, r.y2, r.r, r.g, r.b, speed, 0, 0 };
//                    REctangle down = { r.x1, r.y1, r.x2, cy, r.r, r.g, r.b, speed, 0, 0 };
//
//                    rect.push_back(left);
//                    rect.push_back(right);
//                    rect.push_back(top);
//                    rect.push_back(down);
//
//                    ClickCount++;
//                    break;
//                }
//                else if (ClickCount >= 3)
//                {
//                    float cx = (r.x1 + r.x2) / 2.0f;
//                    float cy = (r.y1 + r.y2) / 2.0f;
//
//                    float w = (r.x2 - r.x1) / 2.0f;
//                    float h = (r.y2 - r.y1) / 2.0f;
//
//                    rect.erase(rect.begin() + i);
//
//                    float speed = 0.03f;
//
//                    REctangle left = { r.x1, r.y1, cx, r.y2, r.r, r.g, r.b, -speed, 0, 0 };
//                    REctangle right = { cx, r.y1, r.x2, r.y2, r.r, r.g, r.b, speed, 0, 0 };
//                    REctangle top = { r.x1, cy, r.x2, r.y2, r.r, r.g, r.b, 0, speed, 0 };
//                    REctangle down = { r.x1, r.y1, r.x2, cy, r.r, r.g, r.b, 0, -speed, 0 };
//                    // 대각선 분할
//                    REctangle leftTop = { r.x1, cy, cx, r.y2, r.r, r.g, r.b, -speed, speed, 1 };
//                    REctangle rightTop = { cx, cy, r.x2, r.y2, r.r, r.g, r.b, speed, speed, 1 };
//                    REctangle leftBottom = { r.x1, r.y1, cx, cy, r.r, r.g, r.b, -speed, -speed, 1 };
//                    REctangle rightBottom = { cx, r.y1, r.x2, cy, r.r, r.g, r.b, speed, -speed, 1 };
//                    rect.push_back(left);
//                    rect.push_back(right);
//                    rect.push_back(top);
//                    rect.push_back(down);
//                    rect.push_back(leftTop);
//                    rect.push_back(rightTop);
//                    rect.push_back(leftBottom);
//                    rect.push_back(rightBottom);
//                    break;
//                }
//
//                break;
//            }
//        }
//    }
//    glutPostRedisplay();
//}
//
//
//
//
//
//
//void Motion(int x, int y) {}
//
//
//void main(int argc, char** argv)
//{
//    srand((unsigned int)time(NULL));
//    for (int i = 0; i < 7; i++)
//    {
//		REctangle r;
//		r.x1 = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
//		r.y1 = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
//		r.x2 = r.x1 + (float)rand() / RAND_MAX * (0.5f - 0.1f) + 0.1f;
//		r.y2 = r.y1 + (float)rand() / RAND_MAX * (0.5f - 0.1f) + 0.1f ;
//		r.r = (float)rand() / RAND_MAX;
//		r.g = (float)rand() / RAND_MAX;
//		r.b = (float)rand() / RAND_MAX;
//		rect.push_back(r);
//    }
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
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//	for (int i = 0; i < rect.size(); i++)
//		Draw_Shape(rect[i]);
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
//
//    }
//    glutPostRedisplay();
//}