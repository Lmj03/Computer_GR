//#include <iostream>
//#include <gl/glew.h> //--- 필요한 헤더파일 include
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
//		// 내부 클릭 - 클릭 위치로 사분면 판단
//		if (nx > 0 && ny > 0) return 1; // 1사분면
//		if (nx < 0 && ny > 0) return 2; // 2사분면
//		if (nx < 0 && ny < 0) return 3; // 3사분면
//		if (nx > 0 && ny < 0) return 4; // 4사분면
//	}
//	else {
//		// 외부 클릭 - 클릭 위치로 사분면 판단
//		if (nx > 0 && ny > 0) return 5; // 1사분면 외부
//		if (nx < 0 && ny > 0) return 6; // 2사분면 외부
//		if (nx < 0 && ny < 0) return 7; // 3사분면 외부
//		if (nx > 0 && ny < 0) return 8; // 4사분면 외부
//	}
//
//	return 0; // 축 위나 기타
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
//    // 먼저 클릭 위치가 어느 사분면인지 판단
//    int clickQuadrant = 0;
//    if (nx > 0 && ny > 0) clickQuadrant = 1;      // 1사분면
//    else if (nx < 0 && ny > 0) clickQuadrant = 2; // 2사분면  
//    else if (nx < 0 && ny < 0) clickQuadrant = 3; // 3사분면
//    else if (nx > 0 && ny < 0) clickQuadrant = 4; // 4사분면
//
//    printf("Click is in quadrant: %d\n", clickQuadrant);
//
//    // 해당 사분면의 사각형만 체크
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
//            range = clickQuadrant; // 내부 클릭
//            printf("Inside rectangle %d\n", rectIndex);
//        }
//        else {
//            range = clickQuadrant + 4; // 외부 클릭 (5,6,7,8)
//            printf("Outside rectangle %d\n", rectIndex);
//        }
//    }
//
//    printf("Final range: %d\n", range);
//
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//    {
//        if (range == 1) // 1사분면
//            rect[0].r = (float)rand() / RAND_MAX, rect[0].g = (float)rand() / RAND_MAX, rect[0].b = (float)rand() / RAND_MAX;
//        else if (range == 2) // 2사분면
//            rect[1].r = (float)rand() / RAND_MAX, rect[1].g = (float)rand() / RAND_MAX, rect[1].b = (float)rand() / RAND_MAX;
//        else if (range == 3) // 3사분면
//            rect[2].r = (float)rand() / RAND_MAX, rect[2].g = (float)rand() / RAND_MAX, rect[2].b = (float)rand() / RAND_MAX;
//        else if (range == 4) // 4사분면
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
//        // 기존 우클릭 처리 코드 동일...
//        if (range == 1) // 1사분면
//        {
//            if (rect[0].x1 + 0.1f >= rect[0].x2 - 0.1f) return;
//            rect[0].x1 += 0.1f;
//            rect[0].y1 += 0.1f;
//            rect[0].x2 -= 0.1f;
//            rect[0].y2 -= 0.1f;
//        }
//        else if (range == 2) // 2사분면
//        {
//            if (rect[1].x1 - 0.1f <= rect[1].x2 + 0.1f) return;
//            rect[1].x1 -= 0.1f;
//            rect[1].y1 += 0.1f;
//            rect[1].x2 += 0.1f;
//            rect[1].y2 -= 0.1f;
//        }
//        else if (range == 3) // 3사분면
//        {
//            if (rect[2].x1 - 0.1f <= rect[2].x2 + 0.1f) return;
//            rect[2].x1 -= 0.1f;
//            rect[2].y1 -= 0.1f;
//            rect[2].x2 += 0.1f;
//            rect[2].y2 += 0.1f;
//        }
//        else if (range == 4) // 4사분면
//        {
//            if (rect[3].x1 + 0.1f >= rect[3].x2 - 0.1f) return;
//            rect[3].x1 += 0.1f;
//            rect[3].y1 -= 0.1f;
//            rect[3].x2 -= 0.1f;
//            rect[3].y2 += 0.1f;
//        }
//        else if (range == 5) // 1사분면 외부
//        {
//            if (rect[0].x1 - 0.1f <= -1.0f) return;
//            rect[0].x1 -= 0.1f;
//            rect[0].y1 -= 0.1f;
//            rect[0].x2 += 0.1f;
//            rect[0].y2 += 0.1f;
//        }
//        else if (range == 6) // 2사분면 외부
//        {
//            if (rect[1].x1 + 0.1f >= 0.0f) return;
//            rect[1].x1 += 0.1f;
//            rect[1].y1 -= 0.1f;
//            rect[1].x2 -= 0.1f;
//            rect[1].y2 += 0.1f;
//        }
//        else if (range == 7) // 3사분면 외부
//        {
//            if (rect[2].x1 + 0.1f >= 0.0f) return;
//            rect[2].x1 += 0.1f;
//            rect[2].y1 += 0.1f;
//            rect[2].x2 -= 0.1f;
//            rect[2].y2 -= 0.1f;
//        }
//        else if (range == 8) // 4사분면 외부
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
//void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
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
//	//--- 윈도우 생성하기
//	glutInit(&argc, argv); //--- glut 초기화
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //--- 디스플레이 모드 설정
//	glutInitWindowPosition(0, 0); //--- 윈도우의 위치 지정
//	glutInitWindowSize(800, 600); //--- 윈도우의 크기 지정
//	glutCreateWindow("Example1"); //--- 윈도우 생성(윈도우 이름)
//	//--- GLEW 초기화하기
//	glewExperimental = GL_TRUE;
//	if (glewInit() != GLEW_OK) //--- glew 초기화 
//	{
//		std::cerr << "Unable to initialize GLEW" << std::endl;
//		exit(EXIT_FAILURE);
//	}
//	else
//		std::cout << "GLEW Initialized\n";
//	glutDisplayFunc(drawScene); //--- 출력 콜백함수의 지정
//	glutReshapeFunc(Reshape); //--- 다시 그리기 콜백함수 지정
//	glutKeyboardFunc(Keyboard); //--- 키보드 입력 콜백함수 지정
//	glutMouseFunc(Mouse); //--- 마우스 입력 콜백함수 지정
//	glutTimerFunc(100, TimerFunction, 1);	// 타이머 콜백함수 지정
//	glutMainLoop(); //--- 이벤트 처리 시작
//}
//GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
//{
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //--- 바탕색을 변경
//	glClear(GL_COLOR_BUFFER_BIT); //--- 설정된 색으로 전체를 칠하기
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
//	glutSwapBuffers(); //--- 화면에 출력하기
//}
//GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
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
//	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
//}