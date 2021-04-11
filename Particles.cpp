// ---------------------------------------------
// Управление:
// 1,2 - Изменить радиус потока частиц
// 3,4 - Изменить размер частиц
// W,A,S,D - Изменить направление потока частиц
// Q,E - Изменить яркость частиц
// I,J,K,L - Изменить позицию источника частиц
// ---------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include<math.h>
#include <Windows.h>
#include "GLtools.h"
#include "GLUT.h"
#include"GLU.h"
#include"GL.h"
#include"GLAUX.h"

#define MAX_PARTICLES 1000          // Максимальное количество частиц

float rad_size = 30.0f;             // Размер "радиуса" потока частиц

float particle_size = 1;           // Размер частицы

float xg = 25.0f;                   // Направление частицы по X
float yg = 25.0f;                   // Направление частицы по Y

float xpos = 0.0f;                  // Позиця частицы по X
float ypos = 0.0f;                  // Позиция частицы по Y

float color = 0.1f;                 // Переменная для изменения яркости цвета частиц

GLuint loop;                        // Переменная цикла

typedef struct
{
	float life;                     // Продолжительность жизни частицы
	float fade;                     // Быстрота гибели частицы
	float x, y;                     // Позиция частицы по X и Y
	float r, g, b;                  // Цвет частицы в RGB
	float xi, yi;                   // Направление частицы по X и Y
}

particles;                          // Структура частиц

particles particle[MAX_PARTICLES];  // Массив хранения информации о частицах

GLfloat winWidth = 800.0f;          // Ширина окна
GLfloat winHeight = 600.0f;         // Высота окна

void CreateWin(const char* title, GLfloat winWidth, GLfloat winHeight)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(title);
}

void ReshapeWin(int winWidth, int winHeight)
{
	glViewport(0.0f, 0.0f, winWidth, winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, winWidth, winHeight, 0.0f, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
}

void InitScene()
{
	/*glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0.0f, 0.0f, winWidth, winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 800.0f, 600.0f, 0.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);*/

	for (loop = 0; loop < MAX_PARTICLES; loop++)
	{
		particle[loop].life = 1.0f;
		particle[loop].fade = 0.001f;               // Создаём в начале взрыв

		particle[loop].x = 395.0f + xpos;
		particle[loop].y = 295.0f + ypos;

		particle[loop].r = (float(rand() % 100) / 100.0f) + color;
		particle[loop].g = (float(rand() % 100) / 100.0f) + color;
		particle[loop].b = (float(rand() % 100) / 100.0f) + color;

		particle[loop].xi = float((rand() % 50) - xg) * 30.0f;
		particle[loop].yi = float((rand() % 50) - yg) * 30.0f;


	}
}

void Draw(void)
{

	for (loop = 0; loop < MAX_PARTICLES; loop++)
	{
		float x = particle[loop].x;
		float y = particle[loop].y;

		glColor4f(particle[loop].r, particle[loop].g, particle[loop].b, particle[loop].life);

		glRectf(x, y, x + particle_size, y + particle_size);

		particle[loop].x += particle[loop].xi / 1000;
		particle[loop].y += particle[loop].yi / 1000;

		particle[loop].life -= particle[loop].fade;

		if (particle[loop].life < 0.0f)
		{
			particle[loop].life = 1.0f;

			particle[loop].fade = (float(rand() % 100) / 1000.0f) + 0.003f;       // 0.003f добавляется для того чтобы число не могло быть равно 0

			particle[loop].x = 395.0f + xpos;
			particle[loop].y = 295.0f + ypos;

			particle[loop].r = (float(rand() % 100) / 100.0f) + color;
			particle[loop].g = (float(rand() % 100) / 100.0f) + color;
			particle[loop].b = (float(rand() % 100) / 100.0f) + color;

			particle[loop].xi = float((rand() % 50) - xg) * rad_size;
			particle[loop].yi = float((rand() % 50) - yg) * rad_size;

		}
	}

}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	Draw();
	glutPostRedisplay();
	glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y)
{
	if (key == '1') {
		rad_size -= 2.0f;
	}

	if (key == '2') {
		rad_size += 2.0f;
	}

	if (key == '3') {
		particle_size -= 1.0f;
	}

	if (key == '4') {
		particle_size += 1.0f;
	}

	if (key == 'a') {
		xg += 7.0f;
	}

	if (key == 'd') {
		xg -= 7.0f;
	}

	if (key == 'w') {
		yg += 7.0f;
	}

	if (key == 's') {
		yg -= 7.0f;
	}

	if (key == 'q') {
		color += 0.1f;
	}

	if (key == 'e') {
		color -= 0.1f;
	}

	if (key == 'i') {
		ypos -= 10.0f;
	}

	if (key == 'k') {
		ypos += 10.0f;
	}

	if (key == 'j') {
		xpos -= 10.0f;
	}

	if (key == 'l') {
		xpos += 10.0f;
	}

}

void main(void)
{
	CreateWin("Particle System", winWidth, winHeight);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0.0f, 0.0f, winWidth, winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 800.0f, 600.0f, 0.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);

	InitScene();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ReshapeWin);
	glutKeyboardFunc(keyPressed);
	glutMainLoop();
}
