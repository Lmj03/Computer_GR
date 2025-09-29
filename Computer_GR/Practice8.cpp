//--- 필요한 헤더파일 선언
#define _CRT_SECURE_NO_WARNINGS //--- 프로그램 맨 앞에 선언할 것
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <time.h>

//--- 함수 선언 추가하기
GLfloat triShape[100][4];
GLfloat colors[100][3];
GLuint vao, vbo[2];

int ClickCount = 0, Shape_Mode = 0;
bool clickOn = false;
int selectedIndex = -1; // 선택된 도형의 시작 인덱스 저장

void InitBuffer()
{
	glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(vao); //--- VAO를 바인드하기
	glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기
	//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//--- 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
	//--- triShape 배열의 사이즈: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 400 * sizeof(GLfloat), triShape, GL_STATIC_DRAW);
	//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 0번을 사용가능하게 함
	glEnableVertexAttribArray(0);
	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- 변수 colors에서 버텍스 색상을 복사한다.
	//--- colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 400 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 1번을 사용 가능하게 함.
	glEnableVertexAttribArray(1);
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}

//--- 아래 5개 함수는 사용자 정의 함수 임
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
//--- 필요한 변수 선언
GLint width, height;
GLuint shaderProgramID; //--- 세이더 프로그램 이름
GLuint vertexShader; //--- 버텍스 세이더 객체
GLuint fragmentShader; //--- 프래그먼트 세이더 객체

void TimerFunction(int value)
{

	glutTimerFunc(16, TimerFunction, 1);
}

bool isInside(float mx, float my, int index)
{
	int type = (int)triShape[index][3];
	if (type == 0) // 점
	{
		float dx = triShape[index][0] - mx;
		float dy = triShape[index][1] - my;
		return (dx * dx + dy * dy < 0.02f * 0.02f); // 반경 0.02 안에 있으면 클릭
	}
	else if (type == 1) // 선
	{
		float x1 = triShape[index][0], y1 = triShape[index][1];
		float x2 = triShape[index + 1][0], y2 = triShape[index + 1][1];
		// 간단히: 선분의 AABB(사각형 영역)으로 체크
		float minx = std::min(x1, x2), maxx = std::max(x1, x2);
		float miny = std::min(y1, y2), maxy = std::max(y1, y2);
		return (mx >= minx - 0.02f && mx <= maxx + 0.02f &&
			my >= miny - 0.02f && my <= maxy + 0.02f);
	}
	else if (type == 2) // 삼각형
	{
		// AABB로 단순 체크
		float minx = std::min({ triShape[index][0], triShape[index + 1][0], triShape[index + 2][0] });
		float maxx = std::max({ triShape[index][0], triShape[index + 1][0], triShape[index + 2][0] });
		float miny = std::min({ triShape[index][1], triShape[index + 1][1], triShape[index + 2][1] });
		float maxy = std::max({ triShape[index][1], triShape[index + 1][1], triShape[index + 2][1] });
		return (mx >= minx && mx <= maxx && my >= miny && my <= maxy);
	}
	else if (type == 3) // 사각형
	{
		// 두 개 삼각형이니까 6개 정점 중 min/max
		float minx = triShape[index][0], maxx = triShape[index][0];
		float miny = triShape[index][1], maxy = triShape[index][1];
		for (int j = 0; j < 6; j++)
		{
			minx = std::min(minx, triShape[index + j][0]);
			maxx = std::max(maxx, triShape[index + j][0]);
			miny = std::min(miny, triShape[index + j][1]);
			maxy = std::max(maxy, triShape[index + j][1]);
		}
		return (mx >= minx && mx <= maxx && my >= miny && my <= maxy);
	}
	return false;
}


void Mouse(int button, int state, int x, int y)
{
	float nx = (float)x / 400.0f - 1.0f;
	float ny = 1.0f - (float)y / 300.0f;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
		if(Shape_Mode == 0)//점 그리기
		{
			if (ClickCount >= 40) return;
			triShape[ClickCount][0] = nx;
			triShape[ClickCount][1] = ny;
			triShape[ClickCount][2] = 0.0f;
			triShape[ClickCount][3] = Shape_Mode;
			std::cout << "x: " << nx << ", y: " << ny << std::endl;
			colors[ClickCount][0] = (float)rand() / RAND_MAX;
			colors[ClickCount][1] = (float)rand() / RAND_MAX;
			colors[ClickCount][2] = (float)rand() / RAND_MAX;
			//좌표 버퍼 전달
			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, ClickCount * 4 * sizeof(GLfloat), triShape);
			//--- 사용자가 정의한 데이터를 현재 바인딩된 버퍼에 복사한다
			//색상 버퍼 전달
			glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);
			ClickCount++;
		}
		else if (Shape_Mode == 1)//선 그리기
		{
			if (ClickCount >= 40) return;
			for(int i =0;i<2;i++)
			{
				triShape[ClickCount][0] = nx-(i*0.3f);
				triShape[ClickCount][1] = ny;
				triShape[ClickCount][2] = 0.0f;
				triShape[ClickCount][3] = Shape_Mode;
				std::cout << "x: " << nx << ", y: " << ny << std::endl;
				colors[ClickCount][0] = (float)rand() / RAND_MAX;
				colors[ClickCount][1] = (float)rand() / RAND_MAX;
				colors[ClickCount][2] = (float)rand() / RAND_MAX;
				
				ClickCount++;

			}

		}
		else if (Shape_Mode == 2)
		{
			if (ClickCount >= 40) return;
			for (int i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					triShape[ClickCount][0] = nx;
					triShape[ClickCount][1] = ny+0.1f;
				}
				else if(i == 1)
				{
					triShape[ClickCount][0] = nx -0.1f;
					triShape[ClickCount][1] = ny;
				}
				else
				{
					triShape[ClickCount][0] = nx+0.1f;
					triShape[ClickCount][1] = ny;
				}
				triShape[ClickCount][2] = 0.0f;
				triShape[ClickCount][3] = Shape_Mode;
				std::cout << "x: " << nx << ", y: " << ny << std::endl;
				colors[ClickCount][0] = (float)rand() / RAND_MAX;
				colors[ClickCount][1] = (float)rand() / RAND_MAX;
				colors[ClickCount][2] = (float)rand() / RAND_MAX;
				ClickCount++;
				
			}
		}
		else if (Shape_Mode == 3)
		{
			if (ClickCount >= 40) return;
			for (int i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					triShape[ClickCount][0] = nx;
					triShape[ClickCount][1] = ny + 0.1f;
				}
				else if (i == 1)
				{
					triShape[ClickCount][0] = nx - 0.1f;
					triShape[ClickCount][1] = ny;
				}
				else
				{
					triShape[ClickCount][0] = nx + 0.1f;
					triShape[ClickCount][1] = ny;
				}
				triShape[ClickCount][2] = 0.0f;
				triShape[ClickCount][3] = Shape_Mode;
				std::cout << "x: " << nx << ", y: " << ny << std::endl;
				colors[ClickCount][0] = (float)rand() / RAND_MAX;
				colors[ClickCount][1] = (float)rand() / RAND_MAX;
				colors[ClickCount][2] = (float)rand() / RAND_MAX;
				ClickCount++;
			}
			for (int i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					triShape[ClickCount][0] = nx;
					triShape[ClickCount][1] = ny-0.1f;
				}
				else if (i == 1)
				{
					triShape[ClickCount][0] = nx+0.1f;
					triShape[ClickCount][1] = ny;
				}
				else
				{
					triShape[ClickCount][0] = nx-0.1f;
					triShape[ClickCount][1] = ny;
				}
				triShape[ClickCount][2] = 0.0f;
				triShape[ClickCount][3] = Shape_Mode;
				std::cout << "x: " << nx << ", y: " << ny << std::endl;
				colors[ClickCount][0] = (float)rand() / RAND_MAX;
				colors[ClickCount][1] = (float)rand() / RAND_MAX;
				colors[ClickCount][2] = (float)rand() / RAND_MAX;
				ClickCount++;
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, ClickCount * 4 * sizeof(GLfloat), triShape);
		//--- 사용자가 정의한 데이터를 현재 바인딩된 버퍼에 복사한다
		//색상 버퍼 전달
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// 클릭한 위치에 있는 도형 찾기
		selectedIndex = -1;
		for (int i = 0; i < ClickCount; )
		{
			if (isInside(nx, ny, i))
			{
				selectedIndex = i;
				break;
			}
			int type = (int)triShape[i][3];
			if (type == 0) i += 1;
			else if (type == 1) i += 2;
			else if (type == 2) i += 3;
			else if (type == 3) i += 6;
			else i++;
		}
		if (selectedIndex != -1)
		{
			std::cout << "Selected shape at index: " << selectedIndex << std::endl;
			clickOn = true;
		}
		else
		{
			clickOn = false;
		}
	}
	glutPostRedisplay();
}

void Motion(int x, int y) {}



//--- 메인 함수
void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	width = 800;
	height = 600;
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();
	//--- 세이더 읽어와서 세이더 프로그램 만들기: 사용자 정의함수 호출
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	shaderProgramID = make_shaderProgram();
	InitBuffer();
	//--- 세이더 프로그램 만들기
	glutDisplayFunc(drawScene); //--- 출력 콜백 함수
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMotionFunc(Motion);
	glutMouseFunc(Mouse);
	glutTimerFunc(16, TimerFunction, 1);
	glutMainLoop();
}

void make_vertexShaders()
{
	GLchar* vertexSource;
	//--- 버텍스 세이더 읽어 저장하고 컴파일 하기
	//--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if(!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "“ERROR: vertex shader 컴파일 실패\n”" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	GLchar* fragmentSource;
	//--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
	fragmentSource = filetobuf("fragment.glsl"); // 프래그세이더 읽어오기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

GLuint make_shaderProgram()
{
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	GLuint shaderID;
	GLint result;
	GLchar errorLog[512];
	shaderID = glCreateProgram(); //--- 세이더 프로그램 만들기
	glAttachShader(shaderID, vertexShader); //--- 세이더 프로그램에 버텍스 세이더 붙이기
	glAttachShader(shaderID, fragmentShader); //--- 세이더 프로그램에 프래그먼트 세이더 붙이기
	glLinkProgram(shaderID); //--- 세이더 프로그램 링크하기
	glDeleteShader(vertexShader); //--- 세이더 객체를 세이더 프로그램에 링크했음으로, 세이더 객체 자체는 삭제 가능
	glDeleteShader(fragmentShader);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result); // ---세이더가 잘 연결되었는지 체크하기
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
		return false;
	}
	glUseProgram(shaderID); //--- 만들어진 세이더 프로그램 사용하기
	//--- 여러 개의 세이더프로그램 만들 수 있고, 그 중 한개의 프로그램을 사용하려면
	//--- glUseProgram 함수를 호출하여 사용 할 특정 프로그램을 지정한다.
	//--- 사용하기 직전에 호출할 수 있다.
	return shaderID;
}

//--- 출력 콜백 함수
GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	//glClearColor(rColor, gColor, bColor, 1.0f);
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(shaderProgramID);
	//--- 사용할 VAO 불러오기
	glBindVertexArray(vao);
	//--- 삼각형 그리기
	glPointSize(10.0f);
	for (int i = 0; i < ClickCount; i++)
	{
		if (triShape[i][3] == 0)//점
			glDrawArrays(GL_POINTS, i, 1);
		else if (triShape[i][3] == 1)//선
		{
			glDrawArrays(GL_LINES, i, 2);
			i++;
		}
		else if (triShape[i][3] == 2)//삼각형
		{
			glDrawArrays(GL_TRIANGLES, i, 3);
			i += 2;
		}
		else if (triShape[i][3] == 3)//사각형
		{
			glDrawArrays(GL_TRIANGLES, i, 3);
			glDrawArrays(GL_TRIANGLES, i+3, 3);
			i += 5;
		}
	}
	glutSwapBuffers(); //--- 화면에 출력하기
}
//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		
	case 'w'://위로 이동
		if (triShape[selectedIndex][3] == 0)
		{
			triShape[selectedIndex][1] += 0.05f;
			if (triShape[selectedIndex][1] > 1.0f) triShape[selectedIndex][1] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 1)
		{
			triShape[selectedIndex][1] += 0.05f;
			triShape[selectedIndex + 1][1] += 0.05f;
			if (triShape[selectedIndex][1] > 1.0f) triShape[selectedIndex][1] = 1.0f;
			if (triShape[selectedIndex + 1][1] > 1.0f) triShape[selectedIndex + 1][1] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 2)
		{
			triShape[selectedIndex][1] += 0.05f;
			triShape[selectedIndex + 1][1] += 0.05f;
			triShape[selectedIndex + 2][1] += 0.05f;
			if (triShape[selectedIndex][1] > 1.0f) triShape[selectedIndex][1] = 1.0f;
			if (triShape[selectedIndex + 1][1] > 1.0f) triShape[selectedIndex + 1][1] = 1.0f;
			if (triShape[selectedIndex + 2][1] > 1.0f) triShape[selectedIndex + 2][1] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 3)
		{
			for (int i = 0; i < 6; i++)
			{
				triShape[selectedIndex + i][1] += 0.05f;
				if (triShape[selectedIndex + i][1] > 1.0f) triShape[selectedIndex + i][1] = 1.0f;
			}

		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, ClickCount * 4 * sizeof(GLfloat), triShape);
		break;
	case 's': // 밑으로 이동
		if (triShape[selectedIndex][3] == 0)
		{
			triShape[selectedIndex][1] -= 0.05f;
			if (triShape[selectedIndex][1] < -1.0f) triShape[selectedIndex][1] = -1.0f;
		}
		else if (triShape[selectedIndex][3] == 1)
		{
			triShape[selectedIndex][1] -= 0.05f;
			triShape[selectedIndex + 1][1] -= 0.05f;
			if (triShape[selectedIndex][1] < -1.0f) triShape[selectedIndex][1] = -1.0f;
			if (triShape[selectedIndex + 1][1] < -1.0f) triShape[selectedIndex + 1][1] = -1.0f;
		}
		else if (triShape[selectedIndex][3] == 2)
		{
			triShape[selectedIndex][1] -= 0.05f;
			triShape[selectedIndex + 1][1] -= 0.05f;
			triShape[selectedIndex + 2][1] -= 0.05f;
			if (triShape[selectedIndex][1] < -1.0f) triShape[selectedIndex][1] = -1.0f;
			if (triShape[selectedIndex + 1][1] < -1.0f) triShape[selectedIndex + 1][1] = -1.0f;
			if (triShape[selectedIndex + 2][1] < -1.0f) triShape[selectedIndex + 2][1] = -1.0f;
		}
		else if (triShape[selectedIndex][3] == 3)
		{
			for (int i = 0; i < 6; i++)
			{
				triShape[selectedIndex + i][1] -= 0.05f;
				if (triShape[selectedIndex + i][1] < -1.0f) triShape[selectedIndex + i][1] = -1.0f;
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, ClickCount * 4 * sizeof(GLfloat), triShape);
		break;
	case 'a': //왼쪽으로 이동
		if (triShape[selectedIndex][3] == 0)
		{
			triShape[selectedIndex][0] -= 0.05f;
			if (triShape[selectedIndex][0] < -1.0f) triShape[selectedIndex][0] = -1.0f;
		}
		else if (triShape[selectedIndex][3] == 1)
		{
			triShape[selectedIndex][0] -= 0.05f;
			triShape[selectedIndex + 1][0] -= 0.05f;
			if (triShape[selectedIndex][0] < -1.0f) triShape[selectedIndex][0] = -1.0f;
			if (triShape[selectedIndex + 1][0] < -1.0f) triShape[selectedIndex + 1][0] = -1.0f;
		}
		else if (triShape[selectedIndex][3] == 2)
		{
			triShape[selectedIndex][0] -= 0.05f;
			triShape[selectedIndex + 1][0] -= 0.05f;
			triShape[selectedIndex + 2][0] -= 0.05f;
			if (triShape[selectedIndex][0] < -1.0f) triShape[selectedIndex][0] = -1.0f;
			if (triShape[selectedIndex + 1][0] < -1.0f) triShape[selectedIndex + 1][0] = -1.0f;
			if (triShape[selectedIndex + 2][0] < -1.0f) triShape[selectedIndex + 2][0] = -1.0f;
		}
		else if (triShape[selectedIndex][3] == 3)
		{
			for (int i = 0; i < 6; i++)
			{
				triShape[selectedIndex + i][0] -= 0.05f;
				if (triShape[selectedIndex + i][0] < -1.0f) triShape[selectedIndex + i][0] = -1.0f;
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, ClickCount * 4 * sizeof(GLfloat), triShape);
		break;
	case 'd': //오른쪽으로 이동
		if (triShape[selectedIndex][3] == 0)
		{
			triShape[selectedIndex][0] += 0.05f;
			if (triShape[selectedIndex][0] > 1.0f) triShape[selectedIndex][0] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 1)
		{
			triShape[selectedIndex][0] += 0.05f;
			triShape[selectedIndex + 1][0] += 0.05f;
			if (triShape[selectedIndex][0] > 1.0f) triShape[selectedIndex][0] = 1.0f;
			if (triShape[selectedIndex + 1][0] > 1.0f) triShape[selectedIndex + 1][0] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 2)
		{
			triShape[selectedIndex][0] += 0.05f;
			triShape[selectedIndex + 1][0] += 0.05f;
			triShape[selectedIndex + 2][0] += 0.05f;
			if (triShape[selectedIndex][0] > 1.0f) triShape[selectedIndex][0] = 1.0f;
			if (triShape[selectedIndex + 1][0] > 1.0f) triShape[selectedIndex + 1][0] = 1.0f;
			if (triShape[selectedIndex + 2][0] > 1.0f) triShape[selectedIndex + 2][0] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 3)
		{
			for (int i = 0; i < 6; i++)
			{
				triShape[selectedIndex + i][0] += 0.05f;
				if (triShape[selectedIndex + i][0] > 1.0f) triShape[selectedIndex + i][0] = 1.0f;
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, ClickCount * 4 * sizeof(GLfloat), triShape);
		break;
		
	case 'y': //왼쪽 위대각선으로 이동
		if (triShape[selectedIndex][3] == 0)
		{
			triShape[selectedIndex][0] -= 0.05f;
			if (triShape[selectedIndex][0] < -1.0f) triShape[selectedIndex][0] = -1.0f;
			triShape[selectedIndex][1] += 0.05f;
			if (triShape[selectedIndex][1] > 1.0f) triShape[selectedIndex][1] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 1)
		{
			triShape[selectedIndex][1] += 0.05f;
			triShape[selectedIndex + 1][1] += 0.05f;
			triShape[selectedIndex][0] -= 0.05f;
			triShape[selectedIndex + 1][0] -= 0.05f;

			if (triShape[selectedIndex][1] > 1.0f) triShape[selectedIndex][1] = 1.0f;
			if (triShape[selectedIndex + 1][1] > 1.0f) triShape[selectedIndex + 1][1] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 2)
		{
			triShape[selectedIndex][1] += 0.05f;
			triShape[selectedIndex + 1][1] += 0.05f;
			triShape[selectedIndex + 2][1] += 0.05f;
			triShape[selectedIndex][0] -= 0.05f;
			triShape[selectedIndex + 1][0] -= 0.05f;
			triShape[selectedIndex + 2][0] -= 0.05f;
			if (triShape[selectedIndex][1] > 1.0f) triShape[selectedIndex][1] = 1.0f;
			if (triShape[selectedIndex + 1][1] > 1.0f) triShape[selectedIndex + 1][1] = 1.0f;
			if (triShape[selectedIndex + 2][1] > 1.0f) triShape[selectedIndex + 2][1] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 3)
		{
			for (int i = 0; i < 6; i++)
			{
				triShape[selectedIndex + i][1] += 0.05f;
				triShape[selectedIndex + i][0] -= 0.05f;
				if (triShape[selectedIndex + i][1] > 1.0f) triShape[selectedIndex + i][1] = 1.0f;
			}

		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, ClickCount * 4 * sizeof(GLfloat), triShape);
		break;

	case 'u'://오른쪽 위로 이동
		if (triShape[selectedIndex][3] == 0)
		{
			triShape[selectedIndex][0] += 0.05f;
			if (triShape[selectedIndex][0] > 1.0f) triShape[selectedIndex][0] = 1.0f;
			triShape[selectedIndex][1] += 0.05f;
			if (triShape[selectedIndex][1] > 1.0f) triShape[selectedIndex][1] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 1)
		{
			triShape[selectedIndex][1] += 0.05f;
			triShape[selectedIndex + 1][1] += 0.05f;
			triShape[selectedIndex][0] += 0.05f;
			triShape[selectedIndex + 1][0] += 0.05f;
			if (triShape[selectedIndex][1] > 1.0f) triShape[selectedIndex][1] = 1.0f;
			if (triShape[selectedIndex + 1][1] > 1.0f) triShape[selectedIndex + 1][1] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 2)
		{
			triShape[selectedIndex][1] += 0.05f;
			triShape[selectedIndex + 1][1] += 0.05f;
			triShape[selectedIndex + 2][1] += 0.05f;
			triShape[selectedIndex][0] += 0.05f;
			triShape[selectedIndex + 1][0] += 0.05f;
			triShape[selectedIndex + 2][0] += 0.05f;
			if (triShape[selectedIndex][1] > 1.0f) triShape[selectedIndex][1] = 1.0f;
			if (triShape[selectedIndex + 1][1] > 1.0f) triShape[selectedIndex + 1][1] = 1.0f;
			if (triShape[selectedIndex + 2][1] > 1.0f) triShape[selectedIndex + 2][1] = 1.0f;
		}
		else if (triShape[selectedIndex][3] == 3)
		{
			for (int i = 0; i < 6; i++)
			{
				triShape[selectedIndex + i][1] += 0.05f;
				triShape[selectedIndex + i][0] += 0.05f;
				if (triShape[selectedIndex + i][1] > 1.0f) triShape[selectedIndex + i][1] = 1.0f;
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, ClickCount * 4 * sizeof(GLfloat), triShape);
		break;
	case 'h'://왼쪽 아래 대각선으로 이동
		if (triShape[selectedIndex][3] == 0)
		{
			triShape[selectedIndex][0] -= 0.05f;
			if (triShape[selectedIndex][0] < -1.0f) triShape[selectedIndex][0] = -1.0f;
			triShape[selectedIndex][1] -= 0.05f;
			if (triShape[selectedIndex][1] < -1.0f) triShape[selectedIndex][1] = -1.0f;
		}
		else if (triShape[selectedIndex][3] == 1)
		{
			triShape[selectedIndex][1] -= 0.05f;
			triShape[selectedIndex + 1][1] -= 0.05f;
			triShape[selectedIndex][0] -= 0.05f;
			triShape[selectedIndex + 1][0] -= 0.05f;
			if (triShape[selectedIndex][1] < -1.0f) triShape[selectedIndex][1] = -1.0f;
			if (triShape[selectedIndex + 1][1] < -1.0f) triShape[selectedIndex + 1][1] = -1.0f;
		}
		else if (triShape[selectedIndex][3] == 2)
		{
			triShape[selectedIndex][1] -= 0.05f;
			triShape[selectedIndex + 1][1] -= 0.05f;
			triShape[selectedIndex + 2][1] -= 0.05f;
			triShape[selectedIndex][0] -= 0.05f;
			triShape[selectedIndex + 1][0] -= 0.05f;
			triShape[selectedIndex + 2][0] -= 0.05f;
			if (triShape[selectedIndex][1] < -1.0f) triShape[selectedIndex][1] = -1.0f;
			if (triShape[selectedIndex + 1][1] < -1.0f) triShape[selectedIndex + 1][1] = -1.0f;
			if (triShape[selectedIndex + 2][1] < -1.0f) triShape[selectedIndex + 2][1] = -1.0f;
		}
		else if (triShape[selectedIndex][3] == 3)
		{
			for (int i = 0; i < 6; i++)
			{
				triShape[selectedIndex + i][1] -= 0.05f;
				triShape[selectedIndex + i][0] -= 0.05f;
				if (triShape[selectedIndex + i][1] < -1.0f) triShape[selectedIndex + i][1] = -1.0f;
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, ClickCount * 4 * sizeof(GLfloat), triShape);
		break;
	case 'j'://오른쪽 아래 대각선으로 이동
			if (triShape[selectedIndex][3] == 0)
			{
				triShape[selectedIndex][0] += 0.05f;
				if (triShape[selectedIndex][0] > 1.0f) triShape[selectedIndex][0] = 1.0f;
				triShape[selectedIndex][1] -= 0.05f;
				if (triShape[selectedIndex][1] < -1.0f) triShape[selectedIndex][1] = -1.0f;
			}
			else if (triShape[selectedIndex][3] == 1)
			{
				triShape[selectedIndex][1] -= 0.05f;
				triShape[selectedIndex + 1][1] -= 0.05f;
				triShape[selectedIndex][0] += 0.05f;
				triShape[selectedIndex + 1][0] += 0.05f;
				if (triShape[selectedIndex][1] < -1.0f) triShape[selectedIndex][1] = -1.0f;
				if (triShape[selectedIndex + 1][1] < -1.0f) triShape[selectedIndex + 1][1] = -1.0f;
			}
			else if (triShape[selectedIndex][3] == 2)
			{
				triShape[selectedIndex][1] -= 0.05f;
				triShape[selectedIndex + 1][1] -= 0.05f;
				triShape[selectedIndex + 2][1] -= 0.05f;
				triShape[selectedIndex][0] += 0.05f;
				triShape[selectedIndex + 1][0] += 0.05f;
				triShape[selectedIndex + 2][0] += 0.05f;
				if (triShape[selectedIndex][1] < -1.0f) triShape[selectedIndex][1] = -1.0f;
				if (triShape[selectedIndex + 1][1] < -1.0f) triShape[selectedIndex + 1][1] = -1.0f;
				if (triShape[selectedIndex + 2][1] < -1.0f) triShape[selectedIndex + 2][1] = -1.0f;
			}
			else if (triShape[selectedIndex][3] == 3)
			{
				for (int i = 0; i < 6; i++)
				{
					triShape[selectedIndex + i][1] -= 0.05f;
					triShape[selectedIndex + i][0] += 0.05f;
					if (triShape[selectedIndex + i][1] < -1.0f) triShape[selectedIndex + i][1] = -1.0f;
				}
			}
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, ClickCount * 4 * sizeof(GLfloat), triShape);
		break;

	case 'q':
		exit(0);
		break;
	case 'p':
		Shape_Mode = 0;
		break;
	case 'l':
		Shape_Mode = 1;
		break;
	case 't':
		Shape_Mode = 2;
		break;
	case 'r':
		Shape_Mode = 3;
		break;
	case 'c':
		ClickCount = 0;
		break;
	}
	glutPostRedisplay();
}