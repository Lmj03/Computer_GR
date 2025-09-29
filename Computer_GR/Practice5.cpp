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
//bool ClickOn = false;
//struct REctangle
//{
//	float mx,my;
//	float r, g, b;
//};
//vector<REctangle> rect;
//REctangle Eraser;
//int Erase_Count = 0;
//void REct_init(REctangle& rect)
//{
//	rect.mx = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
//	rect.my = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
//	rect.r = (float)rand() / RAND_MAX;
//	rect.g = (float)rand() / RAND_MAX;
//	rect.b = (float)rand() / RAND_MAX;
//}
//
//void Draw_Shape(REctangle rect)
//{
//	glColor3f(rect.r, rect.g, rect.b);
//	glRectf(rect.mx - 0.05f, rect.my - 0.05f, rect.mx + 0.05f, rect.my + 0.05f);
//}
//
//void Draw_Eraser(REctangle& rect)
//{
//	glColor3f(rect.r, rect.g, rect.b);
//	float size = 0.05f + (float)Erase_Count * 0.01f;
//	glRectf(rect.mx - size, rect.my - size, rect.mx + size, rect.my + size);
//}
//
//void TimerFunction(int value)
//{
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
//        ClickOn = true;
//        Eraser.mx = nx;
//        Eraser.my = ny;
//    }
//    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
//    {
//        ClickOn = false;
//		Erase_Count = 0;
//		Eraser.r = 0.0f; Eraser.g = 0.0f; Eraser.b = 0.0f;
//    }
//    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//    {
//		if (rect.size() >= 30) return;
//		rect.push_back({ nx,ny,(float)rand() / RAND_MAX,(float)rand() / RAND_MAX,(float)rand() / RAND_MAX });
//        Erase_Count--;
//    }
//    glutPostRedisplay();
//}
//
//void Motion(int x, int y)
//{
//    if (ClickOn)
//    {
//		float nx = (float)x / 400.0f - 1.0f;
//		float ny = 1.0f - (float)y / 300.0f;
//		Eraser.mx = nx;
//		Eraser.my = ny;
//        for (int i = 0; i < rect.size(); i++)
//        {
//            float halfSize = 0.05f; // 사각형 한 변의 절반 크기
//
//            if (fabs(rect[i].mx - Eraser.mx) < (halfSize + halfSize) &&
//                fabs(rect[i].my - Eraser.my) < (halfSize + halfSize))
//            {
//                Erase_Count++;
//                Eraser.r = rect[i].r;
//                Eraser.g = rect[i].g;
//                Eraser.b = rect[i].b;
//
//                rect.erase(rect.begin() + i);
//                i--;
//            }
//        }
//		glutPostRedisplay();
//    }
//}
//
//
//void main(int argc, char** argv)
//{
//    srand((unsigned int)time(NULL));
//    for (int i = 0; i < 30; i++)
//    {
//        REctangle r;
//        r.mx = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
//        r.my = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
//        r.r = (float)rand() / RAND_MAX;
//        r.g = (float)rand() / RAND_MAX;
//        r.b = (float)rand() / RAND_MAX;
//        rect.push_back(r);
//    }
//	Eraser = { 0,0,0.5f,0.5f,0.5f };
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
//        Draw_Shape(rect[i]);
//	if(ClickOn) 
//		Draw_Eraser(Eraser);
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
//		rect.clear();
//		for (int i = 0; i < 30; i++)
//		{
//			REctangle r;
//			REct_init(r);
//			rect.push_back(r);
//		}
//		break;
//    }
//    glutPostRedisplay();
//}