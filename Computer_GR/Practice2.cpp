//#include <iostream>
//#include <gl/glew.h> //--- �ʿ��� ������� include
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//#include <stdlib.h>
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid Keyboard(unsigned char key, int x, int y);
//
//struct REctangle {
//	float x1, y1, x2, y2;
//	float r, g, b;
//};
//float B_r =0.3f, B_g=0.3f, B_b=0.3f;
//REctangle rect[4];
//REctangle Backrect[4];
//bool timerOn = false;
//char range;
//void TimerFunction(int value)
//{	
//	glutTimerFunc(100, TimerFunction, 1);
//}
//char Check_Rect(REctangle rect, float nx, float ny)
//{
//	float minX = std::min(rect.x1, rect.x2);
//	float maxX = std::max(rect.x1, rect.x2);
//	float minY = std::min(rect.y1, rect.y2);
//	float maxY = std::max(rect.y1, rect.y2);
//
//	if (nx >= minX && nx <= maxX && ny >= minY && ny <= maxY) {
//		// ���� Ŭ�� - Ŭ�� ��ġ�� ��и� �Ǵ�
//		if (nx > 0 && ny > 0) return 1; // 1��и�
//		if (nx < 0 && ny > 0) return 2; // 2��и�
//		if (nx < 0 && ny < 0) return 3; // 3��и�
//		if (nx > 0 && ny < 0) return 4; // 4��и�
//	}
//	else {
//		// �ܺ� Ŭ�� - Ŭ�� ��ġ�� ��и� �Ǵ�
//		if (nx > 0 && ny > 0) return 5; // 1��и� �ܺ�
//		if (nx < 0 && ny > 0) return 6; // 2��и� �ܺ�
//		if (nx < 0 && ny < 0) return 7; // 3��и� �ܺ�
//		if (nx > 0 && ny < 0) return 8; // 4��и� �ܺ�
//	}
//
//	return 0; // �� ���� ��Ÿ
//
//}
//
//
//
//
//void Mouse(int button, int state, int x, int y)
//{
//    float nx = (float)x / 400.0f - 1.0f;
//    float ny = 1.0f - (float)y / 300.0f;
//
//    printf("Mouse click: (%d, %d) -> OpenGL: (%.2f, %.2f)\n", x, y, nx, ny);
//
//    range = 0;
//
//    // ���� Ŭ�� ��ġ�� ��� ��и����� �Ǵ�
//    int clickQuadrant = 0;
//    if (nx > 0 && ny > 0) clickQuadrant = 1;      // 1��и�
//    else if (nx < 0 && ny > 0) clickQuadrant = 2; // 2��и�  
//    else if (nx < 0 && ny < 0) clickQuadrant = 3; // 3��и�
//    else if (nx > 0 && ny < 0) clickQuadrant = 4; // 4��и�
//
//    printf("Click is in quadrant: %d\n", clickQuadrant);
//
//    // �ش� ��и��� �簢���� üũ
//    if (clickQuadrant >= 1 && clickQuadrant <= 4) {
//        int rectIndex = clickQuadrant - 1; // 0,1,2,3
//
//        float minX = std::min(rect[rectIndex].x1, rect[rectIndex].x2);
//        float maxX = std::max(rect[rectIndex].x1, rect[rectIndex].x2);
//        float minY = std::min(rect[rectIndex].y1, rect[rectIndex].y2);
//        float maxY = std::max(rect[rectIndex].y1, rect[rectIndex].y2);
//
//        printf("Checking rect[%d]: (%.2f,%.2f) to (%.2f,%.2f)\n",
//            rectIndex, minX, minY, maxX, maxY);
//
//        if (nx >= minX && nx <= maxX && ny >= minY && ny <= maxY) {
//            range = clickQuadrant; // ���� Ŭ��
//            printf("Inside rectangle %d\n", rectIndex);
//        }
//        else {
//            range = clickQuadrant + 4; // �ܺ� Ŭ�� (5,6,7,8)
//            printf("Outside rectangle %d\n", rectIndex);
//        }
//    }
//
//    printf("Final range: %d\n", range);
//
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//    {
//        if (range == 1) // 1��и�
//            rect[0].r = (float)rand() / RAND_MAX, rect[0].g = (float)rand() / RAND_MAX, rect[0].b = (float)rand() / RAND_MAX;
//        else if (range == 2) // 2��и�
//            rect[1].r = (float)rand() / RAND_MAX, rect[1].g = (float)rand() / RAND_MAX, rect[1].b = (float)rand() / RAND_MAX;
//        else if (range == 3) // 3��и�
//            rect[2].r = (float)rand() / RAND_MAX, rect[2].g = (float)rand() / RAND_MAX, rect[2].b = (float)rand() / RAND_MAX;
//        else if (range == 4) // 4��и�
//            rect[3].r = (float)rand() / RAND_MAX, rect[3].g = (float)rand() / RAND_MAX, rect[3].b = (float)rand() / RAND_MAX;
//        else if (range == 5)
//            Backrect[0].r = (float)rand() / RAND_MAX, Backrect[0].g = (float)rand() / RAND_MAX, Backrect[0].b = (float)rand() / RAND_MAX;
//        else if(range == 6)
//            Backrect[1].r = (float)rand() / RAND_MAX, Backrect[1].g = (float)rand() / RAND_MAX, Backrect[1].b = (float)rand() / RAND_MAX;
//        else if(range == 7)
//            Backrect[2].r = (float)rand() / RAND_MAX, Backrect[2].g = (float)rand() / RAND_MAX, Backrect[2].b = (float)rand() / RAND_MAX;
//		else if (range == 8)
//            Backrect[3].r = (float)rand() / RAND_MAX, Backrect[3].g = (float)rand() / RAND_MAX, Backrect[3].b = (float)rand() / RAND_MAX;
//    }
//    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//    {
//        // ���� ��Ŭ�� ó�� �ڵ� ����...
//        if (range == 1) // 1��и�
//        {
//            if (rect[0].x1 + 0.1f >= rect[0].x2 - 0.1f) return;
//            rect[0].x1 += 0.1f;
//            rect[0].y1 += 0.1f;
//            rect[0].x2 -= 0.1f;
//            rect[0].y2 -= 0.1f;
//        }
//        else if (range == 2) // 2��и�
//        {
//            if (rect[1].x1 - 0.1f <= rect[1].x2 + 0.1f) return;
//            rect[1].x1 -= 0.1f;
//            rect[1].y1 += 0.1f;
//            rect[1].x2 += 0.1f;
//            rect[1].y2 -= 0.1f;
//        }
//        else if (range == 3) // 3��и�
//        {
//            if (rect[2].x1 - 0.1f <= rect[2].x2 + 0.1f) return;
//            rect[2].x1 -= 0.1f;
//            rect[2].y1 -= 0.1f;
//            rect[2].x2 += 0.1f;
//            rect[2].y2 += 0.1f;
//        }
//        else if (range == 4) // 4��и�
//        {
//            if (rect[3].x1 + 0.1f >= rect[3].x2 - 0.1f) return;
//            rect[3].x1 += 0.1f;
//            rect[3].y1 -= 0.1f;
//            rect[3].x2 -= 0.1f;
//            rect[3].y2 += 0.1f;
//        }
//        else if (range == 5) // 1��и� �ܺ�
//        {
//            if (rect[0].x1 - 0.1f <= -1.0f) return;
//            rect[0].x1 -= 0.1f;
//            rect[0].y1 -= 0.1f;
//            rect[0].x2 += 0.1f;
//            rect[0].y2 += 0.1f;
//        }
//        else if (range == 6) // 2��и� �ܺ�
//        {
//            if (rect[1].x1 + 0.1f >= 0.0f) return;
//            rect[1].x1 += 0.1f;
//            rect[1].y1 -= 0.1f;
//            rect[1].x2 -= 0.1f;
//            rect[1].y2 += 0.1f;
//        }
//        else if (range == 7) // 3��и� �ܺ�
//        {
//            if (rect[2].x1 + 0.1f >= 0.0f) return;
//            rect[2].x1 += 0.1f;
//            rect[2].y1 += 0.1f;
//            rect[2].x2 -= 0.1f;
//            rect[2].y2 -= 0.1f;
//        }
//        else if (range == 8) // 4��и� �ܺ�
//        {
//            if (rect[3].x1 - 0.1f <= 0.0f) return;
//            rect[3].x1 -= 0.1f;
//            rect[3].y1 += 0.1f;
//            rect[3].x2 += 0.1f;
//            rect[3].y2 -= 0.1f;
//        }
//    }
//    glutPostRedisplay();
//}
//
//void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
//{
//    Backrect[0] = { 0.0f, 0.0f, 1.0f, 1.0f };
//    Backrect[1] = { 0.0f, 0.0f, -1.0f, 1.0f };
//    Backrect[2] = { 0.0f, 0.0f, -1.0f, -1.0f };
//    Backrect[3] = { 0.0f, 0.0f, 1.0f, -1.0f };
//	rect[0] = { 0.0f, 0.0f, 1.0f, 1.0f };
//	rect[1] = { 0.0f, 0.0f, -1.0f, 1.0f };
//	rect[2] = { 0.0f, 0.0f, -1.0f, -1.0f };
//	rect[3] = { 0.0f, 0.0f, 1.0f, -1.0f };
//	for (int i = 0; i < 4; i++)
//	{
//		rect[i].r = (float)rand() / RAND_MAX;
//		rect[i].g = (float)rand() / RAND_MAX;
//		rect[i].b = (float)rand() / RAND_MAX;
//		Backrect[i].r = (float)rand() / RAND_MAX;
//		Backrect[i].g = (float)rand() / RAND_MAX;
//		Backrect[i].b = (float)rand() / RAND_MAX;
//	}
//
//	//--- ������ �����ϱ�
//	glutInit(&argc, argv); //--- glut �ʱ�ȭ
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //--- ���÷��� ��� ����
//	glutInitWindowPosition(0, 0); //--- �������� ��ġ ����
//	glutInitWindowSize(800, 600); //--- �������� ũ�� ����
//	glutCreateWindow("Example1"); //--- ������ ����(������ �̸�)
//	//--- GLEW �ʱ�ȭ�ϱ�
//	glewExperimental = GL_TRUE;
//	if (glewInit() != GLEW_OK) //--- glew �ʱ�ȭ 
//	{
//		std::cerr << "Unable to initialize GLEW" << std::endl;
//		exit(EXIT_FAILURE);
//	}
//	else
//		std::cout << "GLEW Initialized\n";
//	glutDisplayFunc(drawScene); //--- ��� �ݹ��Լ��� ����
//	glutReshapeFunc(Reshape); //--- �ٽ� �׸��� �ݹ��Լ� ����
//	glutKeyboardFunc(Keyboard); //--- Ű���� �Է� �ݹ��Լ� ����
//	glutMouseFunc(Mouse); //--- ���콺 �Է� �ݹ��Լ� ����
//	glutTimerFunc(100, TimerFunction, 1);	// Ÿ�̸� �ݹ��Լ� ����
//	glutMainLoop(); //--- �̺�Ʈ ó�� ����
//}
//GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
//{
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //--- �������� ����
//	glClear(GL_COLOR_BUFFER_BIT); //--- ������ ������ ��ü�� ĥ�ϱ�
//    for (int i = 0; i < 4; i++)
//    {
//		glColor3f(Backrect[i].r, Backrect[i].g, Backrect[i].b);
//		glRectf(Backrect[i].x1, Backrect[i].y1, Backrect[i].x2, Backrect[i].y2);
//    }
//	for (int i = 0; i < 4; i++)
//	{
//		glColor3f(rect[i].r, rect[i].g, rect[i].b);
//		glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
//	}
//	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
//}
//GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
//{
//	glViewport(0, 0, w, h);
//}
//GLvoid Keyboard(unsigned char key, int x, int y)
//{
//	switch (key) {
//	case'q':
//		exit(0);
//		break;
//	}
//	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
//}