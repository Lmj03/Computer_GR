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
//    float dx, dy;   // �̵� �ӵ�
//    float originalX, originalY; // ó�� ������ ��ġ
//};
//
//REctangle rect[5];
//int Shape_Count = 0;
//
//int frameCounter = 0; // ������� ��ȯ�� ī����
//int leaderIndex = -1; // ���� �簢�� �ε���
//const int TRAIL_LENGTH = 50; // ���� ����
//Position trail[50]; // ������ �߽� ��ġ ����
//int trailIndex = 0; // ���� ���� �ε���
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
//            // �̵�
//            rect[i].x1 += rect[i].dx;
//            rect[i].x2 += rect[i].dx;
//            rect[i].y1 += rect[i].dy;
//            rect[i].y2 += rect[i].dy;
//
//            // �� �浹
//            if (rect[i].x1 < -1.0f || rect[i].x2 > 1.0f) rect[i].dx *= -1;
//            if (rect[i].y1 < -1.0f || rect[i].y2 > 1.0f) rect[i].dy *= -1;
//
//            // ���� �ֱ⸶�� y ���� ���� �� �������
//            if (frameCounter % 30 == 0) { // 30�����Ӹ��� ���� (�� 0.5��)
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
//    if (on5 && leaderIndex != -1) // ���� ���� �����ϱ�
//    {
//        // ������ ���ο� �̵��� ����
//        float leaderDx = ((float)rand() / RAND_MAX - 0.5f) * 0.02f;
//        float leaderDy = ((float)rand() / RAND_MAX - 0.5f) * 0.02f;
//
//        // ���� �̵�
//        rect[leaderIndex].x1 += leaderDx;
//        rect[leaderIndex].y1 += leaderDy;
//        rect[leaderIndex].x2 += leaderDx;
//        rect[leaderIndex].y2 += leaderDy;
//
//        // �� �浹 üũ
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
//        // ������ �߽� ��ġ�� ������ ����
//        float centerX = (rect[leaderIndex].x1 + rect[leaderIndex].x2) / 2.0f;
//        float centerY = (rect[leaderIndex].y1 + rect[leaderIndex].y2) / 2.0f;
//
//        trail[trailIndex] = { centerX, centerY };
//        trailIndex = (trailIndex + 1) % TRAIL_LENGTH;
//
//        // �ٸ� �簢������ ������ ���� �̵�
//        int followOrder = 1;
//        for (int i = 0; i < Shape_Count; i++) {
//            if (i == leaderIndex) continue;
//
//            // �� �簢���� ���� �Ÿ� ��� (������ �ΰ� ����)
//            int followDistance = followOrder * 8; // 8������ �������� ����
//
//            // �������� ���� ��ġ ���
//            int followTrailIndex = (trailIndex - followDistance + TRAIL_LENGTH) % TRAIL_LENGTH;
//
//            if (followDistance < TRAIL_LENGTH) {
//                Position targetPos = trail[followTrailIndex];
//
//                // ��ǥ ��ġ�� �簢�� �̵� (�߽��� ����)
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
//                // �� ��� üũ (����� �ʵ���)
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
//        rect[Shape_Count].originalX = nx; // ó�� ���� ��ġ ����
//        rect[Shape_Count].originalY = ny;
//        rect[Shape_Count].x1 = nx - 0.1f;
//        rect[Shape_Count].y1 = ny - 0.1f;
//        rect[Shape_Count].x2 = nx + 0.1f;
//        rect[Shape_Count].y2 = ny + 0.1f;
//        rect[Shape_Count].r = (float)rand() / RAND_MAX;
//        rect[Shape_Count].g = (float)rand() / RAND_MAX;
//        rect[Shape_Count].b = (float)rand() / RAND_MAX;
//
//        // �ӵ� ���� ����
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
//        // ���� ��� �ʱ�ȭ
//        for (int i = 0; i < TRAIL_LENGTH; i++) {
//            trail[i] = { 0, 0 };
//        }
//        break;
//    case '1':
//        on1 = !on1;
//        break;
//    case '2':
//        on2 = !on2;
//        frameCounter = 0; // ������ �� ����
//        break;
//    case '3':
//        on3 = !on3;
//        break;
//    case '4':
//        on4 = !on4;
//        break;
//    case '5':
//        if (Shape_Count > 0) {
//            leaderIndex = rand() % Shape_Count; // ���� ���� ����
//            on5 = !on5;
//            trailIndex = 0;
//
//            // ���� ��� �ʱ�ȭ
//            for (int i = 0; i < TRAIL_LENGTH; i++) {
//                trail[i] = { 0, 0 };
//            }
//
//            // ������ ���� ��ġ�� ���� �ʱ�ȭ
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
//        // ��� �簢���� ó�� ������ ��ġ�� �̵� (���� ũ�� ����)
//        for (int i = 0; i < Shape_Count; i++) {
//            // ���� ũ�� ���
//            float currentWidth = rect[i].x2 - rect[i].x1;
//            float currentHeight = rect[i].y2 - rect[i].y1;
//
//            // ���� ��ġ�� �߽����� ���� ũ��� ����
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