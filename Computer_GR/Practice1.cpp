//#include <iostream>
//#include <gl/glew.h> 
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//#include <stdlib.h>
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid Keyboard(unsigned char key, int x, int y);
//
//float r, g, b;
//bool timerOn = false;
//void TimerFunction(int value)
//{
//	if(timerOn)
//	{
//		r = (float)rand() / RAND_MAX;
//		g = (float)rand() / RAND_MAX;
//		b = (float)rand() / RAND_MAX;
//		glutPostRedisplay();
//		glutTimerFunc(100, TimerFunction, 1);
//	}
//}
//void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
//{
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
//	glutTimerFunc(100, TimerFunction, 1);
//	glutMainLoop(); //--- 이벤트 처리 시작
//}
//GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
//{
//	//--- 변경된 배경색 설정
//	glClearColor(r, g, b,1.0f); //--- 바탕색을 변경
//	glClear(GL_COLOR_BUFFER_BIT); //--- 설정된 색으로 전체를 칠하기
//	glutSwapBuffers(); //--- 화면에 출력하기
//}
//GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
//{
//	glViewport(0, 0, w, h);
//}
//GLvoid Keyboard(unsigned char key, int x, int y)
//{
//	switch (key) {
//	case 'c':; 
//		r = 0;
//		g = 1.0f;
//		b = 1.0f;//--- 배경색을 청록색으로 설정
//		break;
//	case 'm':;  //--- 배경색을 자홍색으로 설정
//		r = 1.0f;
//		g = 0;
//		b = 1.0f;
//		break;
//	case 'y':; 
//		r = 1.0f;
//		g = 1.0f;
//		b = 0;
//		break; //--- 배경색을 노랑색으로 설정
//	case 'q':
//		exit(0);
//		break;
//	case 'w':
//		r = 1.0f;
//		g = 1.0f;
//		b = 1.0f;
//		break; //--- 배경색을 흰색으로 설정
//	case 'k':
//		r = 0; g = 0; b = 0;
//		break; //--- 배경색을 검정색으로 설정
//	case 'a':
//		r = (float)rand() / RAND_MAX;
//		g = (float)rand() / RAND_MAX;
//		b = (float)rand() / RAND_MAX;
//		break; //--- 배경색을 랜덤으로 설정
//	case 't':
//		if (!timerOn)
//		{
//			timerOn = true;
//			glutTimerFunc(100, TimerFunction, 1);
//		}
//		break;
//	case 's':
//		if (timerOn) timerOn = false;
//		break; // 타이머 중지
//	}
//	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
//}