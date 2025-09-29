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
//void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
//{
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
//	glutTimerFunc(100, TimerFunction, 1);
//	glutMainLoop(); //--- �̺�Ʈ ó�� ����
//}
//GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
//{
//	//--- ����� ���� ����
//	glClearColor(r, g, b,1.0f); //--- �������� ����
//	glClear(GL_COLOR_BUFFER_BIT); //--- ������ ������ ��ü�� ĥ�ϱ�
//	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
//}
//GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
//{
//	glViewport(0, 0, w, h);
//}
//GLvoid Keyboard(unsigned char key, int x, int y)
//{
//	switch (key) {
//	case 'c':; 
//		r = 0;
//		g = 1.0f;
//		b = 1.0f;//--- ������ û�ϻ����� ����
//		break;
//	case 'm':;  //--- ������ ��ȫ������ ����
//		r = 1.0f;
//		g = 0;
//		b = 1.0f;
//		break;
//	case 'y':; 
//		r = 1.0f;
//		g = 1.0f;
//		b = 0;
//		break; //--- ������ ��������� ����
//	case 'q':
//		exit(0);
//		break;
//	case 'w':
//		r = 1.0f;
//		g = 1.0f;
//		b = 1.0f;
//		break; //--- ������ ������� ����
//	case 'k':
//		r = 0; g = 0; b = 0;
//		break; //--- ������ ���������� ����
//	case 'a':
//		r = (float)rand() / RAND_MAX;
//		g = (float)rand() / RAND_MAX;
//		b = (float)rand() / RAND_MAX;
//		break; //--- ������ �������� ����
//	case 't':
//		if (!timerOn)
//		{
//			timerOn = true;
//			glutTimerFunc(100, TimerFunction, 1);
//		}
//		break;
//	case 's':
//		if (timerOn) timerOn = false;
//		break; // Ÿ�̸� ����
//	}
//	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
//}