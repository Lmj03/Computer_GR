//--- �ʿ��� ������� ����
#define _CRT_SECURE_NO_WARNINGS //--- ���α׷� �� �տ� ������ ��
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <time.h>

//--- �Լ� ���� �߰��ϱ�
GLfloat triShape[100][4];
GLfloat colors[100][3];
GLuint vao, vbo[2];

int ClickCount = 0, Shape_Mode = 0;
bool clickOn = false;
int selectedIndex = -1; // ���õ� ������ ���� �ε��� ����

void InitBuffer()
{
	glGenVertexArrays(1, &vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao); //--- VAO�� ���ε��ϱ�
	glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	//--- triShape �迭�� ������: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 400 * sizeof(GLfloat), triShape, GL_STATIC_DRAW);
	//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 0���� ��밡���ϰ� ��
	glEnableVertexAttribArray(0);
	//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
	//--- colors �迭�� ������: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 400 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 1���� ��� �����ϰ� ��.
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

//--- �Ʒ� 5�� �Լ��� ����� ���� �Լ� ��
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
//--- �ʿ��� ���� ����
GLint width, height;
GLuint shaderProgramID; //--- ���̴� ���α׷� �̸�
GLuint vertexShader; //--- ���ؽ� ���̴� ��ü
GLuint fragmentShader; //--- �����׸�Ʈ ���̴� ��ü

void TimerFunction(int value)
{

	glutTimerFunc(16, TimerFunction, 1);
}

bool isInside(float mx, float my, int index)
{
	int type = (int)triShape[index][3];
	if (type == 0) // ��
	{
		float dx = triShape[index][0] - mx;
		float dy = triShape[index][1] - my;
		return (dx * dx + dy * dy < 0.02f * 0.02f); // �ݰ� 0.02 �ȿ� ������ Ŭ��
	}
	else if (type == 1) // ��
	{
		float x1 = triShape[index][0], y1 = triShape[index][1];
		float x2 = triShape[index + 1][0], y2 = triShape[index + 1][1];
		// ������: ������ AABB(�簢�� ����)���� üũ
		float minx = std::min(x1, x2), maxx = std::max(x1, x2);
		float miny = std::min(y1, y2), maxy = std::max(y1, y2);
		return (mx >= minx - 0.02f && mx <= maxx + 0.02f &&
			my >= miny - 0.02f && my <= maxy + 0.02f);
	}
	else if (type == 2) // �ﰢ��
	{
		// AABB�� �ܼ� üũ
		float minx = std::min({ triShape[index][0], triShape[index + 1][0], triShape[index + 2][0] });
		float maxx = std::max({ triShape[index][0], triShape[index + 1][0], triShape[index + 2][0] });
		float miny = std::min({ triShape[index][1], triShape[index + 1][1], triShape[index + 2][1] });
		float maxy = std::max({ triShape[index][1], triShape[index + 1][1], triShape[index + 2][1] });
		return (mx >= minx && mx <= maxx && my >= miny && my <= maxy);
	}
	else if (type == 3) // �簢��
	{
		// �� �� �ﰢ���̴ϱ� 6�� ���� �� min/max
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
		
		if(Shape_Mode == 0)//�� �׸���
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
			//��ǥ ���� ����
			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, ClickCount * 4 * sizeof(GLfloat), triShape);
			//--- ����ڰ� ������ �����͸� ���� ���ε��� ���ۿ� �����Ѵ�
			//���� ���� ����
			glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);
			ClickCount++;
		}
		else if (Shape_Mode == 1)//�� �׸���
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
		//--- ����ڰ� ������ �����͸� ���� ���ε��� ���ۿ� �����Ѵ�
		//���� ���� ����
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// Ŭ���� ��ġ�� �ִ� ���� ã��
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



//--- ���� �Լ�
void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	width = 800;
	height = 600;
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Example1");
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	glewInit();
	//--- ���̴� �о�ͼ� ���̴� ���α׷� �����: ����� �����Լ� ȣ��
	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	shaderProgramID = make_shaderProgram();
	InitBuffer();
	//--- ���̴� ���α׷� �����
	glutDisplayFunc(drawScene); //--- ��� �ݹ� �Լ�
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
	//--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
	//--- filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
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
		std::cerr << "��ERROR: vertex shader ������ ����\n��" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	GLchar* fragmentSource;
	//--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
	fragmentSource = filetobuf("fragment.glsl"); // �����׼��̴� �о����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

GLuint make_shaderProgram()
{
	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	GLuint shaderID;
	GLint result;
	GLchar errorLog[512];
	shaderID = glCreateProgram(); //--- ���̴� ���α׷� �����
	glAttachShader(shaderID, vertexShader); //--- ���̴� ���α׷��� ���ؽ� ���̴� ���̱�
	glAttachShader(shaderID, fragmentShader); //--- ���̴� ���α׷��� �����׸�Ʈ ���̴� ���̱�
	glLinkProgram(shaderID); //--- ���̴� ���α׷� ��ũ�ϱ�
	glDeleteShader(vertexShader); //--- ���̴� ��ü�� ���̴� ���α׷��� ��ũ��������, ���̴� ��ü ��ü�� ���� ����
	glDeleteShader(fragmentShader);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result); // ---���̴��� �� ����Ǿ����� üũ�ϱ�
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program ���� ����\n" << errorLog << std::endl;
		return false;
	}
	glUseProgram(shaderID); //--- ������� ���̴� ���α׷� ����ϱ�
	//--- ���� ���� ���̴����α׷� ���� �� �ְ�, �� �� �Ѱ��� ���α׷��� ����Ϸ���
	//--- glUseProgram �Լ��� ȣ���Ͽ� ��� �� Ư�� ���α׷��� �����Ѵ�.
	//--- ����ϱ� ������ ȣ���� �� �ִ�.
	return shaderID;
}

//--- ��� �ݹ� �Լ�
GLvoid drawScene()
{
	//--- ����� ���� ����
	//glClearColor(rColor, gColor, bColor, 1.0f);
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(shaderProgramID);
	//--- ����� VAO �ҷ�����
	glBindVertexArray(vao);
	//--- �ﰢ�� �׸���
	glPointSize(10.0f);
	for (int i = 0; i < ClickCount; i++)
	{
		if (triShape[i][3] == 0)//��
			glDrawArrays(GL_POINTS, i, 1);
		else if (triShape[i][3] == 1)//��
		{
			glDrawArrays(GL_LINES, i, 2);
			i++;
		}
		else if (triShape[i][3] == 2)//�ﰢ��
		{
			glDrawArrays(GL_TRIANGLES, i, 3);
			i += 2;
		}
		else if (triShape[i][3] == 3)//�簢��
		{
			glDrawArrays(GL_TRIANGLES, i, 3);
			glDrawArrays(GL_TRIANGLES, i+3, 3);
			i += 5;
		}
	}
	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}
//--- �ٽñ׸��� �ݹ� �Լ�
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		
	case 'w'://���� �̵�
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
	case 's': // ������ �̵�
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
	case 'a': //�������� �̵�
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
	case 'd': //���������� �̵�
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
		
	case 'y': //���� ���밢������ �̵�
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

	case 'u'://������ ���� �̵�
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
	case 'h'://���� �Ʒ� �밢������ �̵�
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
	case 'j'://������ �Ʒ� �밢������ �̵�
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