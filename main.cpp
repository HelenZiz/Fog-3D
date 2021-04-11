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

double x_angle = 0; 
double y_angle = 0;
#define GL_PI 3.1415f
float	angle = 0.0f;
int SceneNumber = 1;


GLTMatrix shadowMat;
int mouse_x = 0, mouse_y = 0, mouse_button = -1, mouse_state = GLUT_UP;

const int ObjectSize = 3;


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	if (h > 0) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, w / (GLdouble)h, 1, 3000);
	}
}

void drawBox(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2)
{
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);

	glBegin(GL_POLYGON);         // front face
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(x1, y1, z2);
	glVertex3f(x2, y1, z2);
	glVertex3f(x2, y2, z2);
	glVertex3f(x1, y2, z2);
	glEnd();

	glBegin(GL_POLYGON);         // back face
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(x2, y1, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y2, z1);
	glVertex3f(x2, y2, z1);
	glEnd();

	glBegin(GL_POLYGON);         // left face
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);
	glVertex3f(x1, y2, z1);
	glEnd();

	glBegin(GL_POLYGON);         //right face
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(x2, y1, z2);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y2, z1);
	glVertex3f(x2, y2, z2);
	glEnd();

	glBegin(GL_POLYGON);         // top face
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(x1, y2, z2);
	glVertex3f(x2, y2, z2);
	glVertex3f(x2, y2, z1);
	glVertex3f(x1, y2, z1);
	glEnd();

	glBegin(GL_POLYGON);         // bottom face
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(x2, y1, z2);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y1, z1);
	glEnd();

	glDisable(GL_POLYGON_SMOOTH);

}

void RenderSurface(int sh)
{
	glBegin(GL_QUADS);
	if (sh == 0) glColor4d(0, 0, 0.9, 0.5);
	else glColor4d(0, 0, 0.9, 0.0);

	glNormal3f(1.0, 0.0, 0.0);
	glVertex3d(-0.3f, 12.0f, 6.0f);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3d(-0.3f, 0.0f, 6.0f);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3d(-0.3f, 0.0f, -15.0f);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3d(-0.3f, 12.0f, -15.0f);
	glEnd();

}

void Area(void)
{
	glBegin(GL_QUADS);
	glColor4d(0, 0.5, 0.0, 0.0);

	glNormal3f(0.0, 1.0, 0.0);
	glVertex3d(0.0f, 0, 6.0f);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3d(-12.0f, 0, 6.0f);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3d(-12.0f, 0, -15.0f);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3d(0.0f, 0, -15.0f);
	glEnd();

}

void DownSurfase()
{

	if ((y_angle > 191) || (y_angle < 15))//||(x_angle>165)||(x_angle<25))//&&(y_angle>15))&&(y_angle>25))
	{
		glBegin(GL_QUADS);
		glColor4d(0.0f, 0.0f, 0.9f, 0.0);
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3d(-0.0f, 0.0f, 6.0f);
		glVertex3d(-0.0f, 12.0f, 6.0f);
		glVertex3d(-0.0f, 12.0f, -15.0f);
		glVertex3d(-0.0f, 0.0f, -15.0f);
		glEnd();
	}
	//боковые стороны
	glBegin(GL_QUAD_STRIP);


	glVertex3d(0.0f, 0.0f, 6.0f);
	glVertex3d(-0.3f, 0.0f, 6.0f);

	glNormal3f(0.0, 0.0, -1.0);
	glVertex3d(0.0f, 12.0f, 6.0f);
	glVertex3d(-0.3f, 12.0f, 6.0f);

	glNormal3f(0.0, -1.0, 0.0);
	glVertex3d(0.0f, 12.0f, -15.0f);
	glVertex3d(-0.3f, 12.0f, -15.0f);

	glNormal3f(0.0, 0.0, 1.0);
	glVertex3d(0.0f, 0.0f, -15.0f);
	glVertex3d(-0.3f, 0.0f, -15.0f);

	glNormal3f(0.0, 1.0, 0.0);
	glVertex3d(0.0f, 0.0f, 6.0f);
	glVertex3d(-0.3f, 0.0f, 6.0f);

	glEnd();

}

void DownArea()
{
	glBegin(GL_QUADS);
	glColor4d(0.0f, 0.0f, 0.9f, 0.0);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3d(0.0f, -0.3f, 6.0f);
	glVertex3d(-12.0f, -0.3f, 6.0f);
	glVertex3d(-12.0f, -0.3f, -15.0f);
	glVertex3d(0.0f, -0.3f, -15.0f);
	glEnd();

	//боковые стороны
	glBegin(GL_QUAD_STRIP);


	glVertex3d(0.0f, 0.0f, 6.0f);
	glVertex3d(0.0f, -0.3f, 6.0f);

	glNormal3f(0.0, 0.0, -1.0);
	glVertex3d(-12.0f, 0.0f, 6.0f);
	glVertex3d(-12.0f, -0.3f, 6.0f);

	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3d(-12.0f, 0.0f, -15.0f);
	glVertex3d(-12.0f, -0.3f, -15.0f);

	glNormal3f(0.0, 0.0, 1.0);
	glVertex3d(0.0f, 0.0f, -15.0f);
	glVertex3d(0.0f, -0.3f, -15.0f);

	glNormal3f(1.0, 0.0, 0.0);
	glVertex3d(0.0f, 0.0f, 6.0f);
	glVertex3d(0.0f, -0.3f, 6.0f);

	glEnd();

}

void ObjectsOnArea(int sh)
{
	GLfloat dt_emissive[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat dt_diffuse[4] = { 0.6f, 0.4f, 0.12f, 0.0f };
	GLfloat dt_specular[4] = { 0.2f, 0.2f, 0.6f, 0.0f };
	GLfloat dt_ambient[4] = { 0.1f, 0.1f, 0.1f, 0.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, dt_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dt_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dt_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dt_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
	glPushMatrix();
	drawBox(-10, -8, 0, 2, -2, 0);
	glPopMatrix();

	GLfloat dm_emissive[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat dm_diffuse[4] = { 0.3f, 0.3f, 0.2f, 0.0f };
	GLfloat dm_specular[4] = { 0.2f, 0.6f, 0.2f, 0.0f };
	GLfloat dm_ambient[4] = { 0.1f, 0.1f, 0.1f, 0.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, dm_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dm_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dm_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dm_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
	glPushMatrix();
	drawBox(-7, -4, 0, 3, 0, 3);
	glPopMatrix();

	GLfloat db_emissive[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat db_diffuse[4] = { 0.1f, 0.5f, 0.8f, 0.0f };
	GLfloat db_specular[4] = { 0.6f, 0.2f, 0.2f, 0.0f };
	GLfloat db_ambient[4] = { 0.1f, 0.1f, 0.1f, 0.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, db_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, db_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, db_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, db_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
	glPushMatrix();
	drawBox(-8, -6, 0, 2, -7, -5);
	glPopMatrix();

}

void	animate()
{
	angle += 2.0f;
	glutPostRedisplay();
}


GLfloat l_position[4] = { -2.0f ,10.0f, 5.0f, 1.0f };
GLfloat FloorMatrix[4][4];
GLfloat Floor[4] = { 0.0, 1.0, 0.0, 0.0 };
GLfloat FloorR[4] = { 1.0, 0.0, 0.0, 8.0 };
GLfloat FloorL[4] = { 0.0, 0.0, 1.0, 0.0 };
void shadowmatrix(GLfloat matrix[4][4], GLfloat plane[4], GLfloat lightpos[4])
{
	GLfloat dot;
	dot = plane[0] * lightpos[0] +
		plane[1] * lightpos[1] +
		plane[2] * lightpos[2] +
		plane[3] * lightpos[3];

	matrix[0][0] = dot - lightpos[0] * plane[0];
	matrix[1][0] = 0.f - lightpos[0] * plane[1];
	matrix[2][0] = 0.f - lightpos[0] * plane[2];
	matrix[3][0] = 0.f - lightpos[0] * plane[3];

	matrix[0][1] = 0.f - lightpos[1] * plane[0];
	matrix[1][1] = dot - lightpos[1] * plane[1];
	matrix[2][1] = 0.f - lightpos[1] * plane[2];
	matrix[3][1] = 0.f - lightpos[1] * plane[3];

	matrix[0][2] = 0.f - lightpos[2] * plane[0];
	matrix[1][2] = 0.f - lightpos[2] * plane[1];
	matrix[2][2] = dot - lightpos[2] * plane[2];
	matrix[3][2] = 0.f - lightpos[2] * plane[3];

	matrix[0][3] = 0.f - lightpos[3] * plane[0];
	matrix[1][3] = 0.f - lightpos[3] * plane[1];
	matrix[2][3] = 0.f - lightpos[3] * plane[2];
	matrix[3][3] = dot - lightpos[3] * plane[3];
}

void Shadow()
{
	//тени на плоскость

	glClear(GL_STENCIL_BUFFER_BIT);

	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glStencilFunc(GL_ALWAYS, 0x1, 0x1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	Area();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 0x1, 0x1);

	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glColor4f(0.0, 0.0, 0.0, 0.5);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(0.0f, 0.01f, 0.0f);
	shadowmatrix(FloorMatrix, Floor, l_position);

	glMultMatrixf((GLfloat*)FloorMatrix);

	ObjectsOnArea(1);

	glPopMatrix();



	glDisable(GL_STENCIL_TEST);
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	//тень на кубик слева

	glClear(GL_STENCIL_BUFFER_BIT);
	
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glStencilFunc(GL_ALWAYS, 0x1, 0x1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);


	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-8.0f, 0.0f, 0.0f);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-10.0f, 2.0f, 0.0f);
	glVertex3f(-8.0f, 2.0f, 0.0f);
	glEnd();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 0x1, 0x1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);


	glColor4f(0.0, 0.0, 0.0, 0.5);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.01);
	shadowmatrix(FloorMatrix, FloorL, l_position);

	glMultMatrixf((GLfloat*)FloorMatrix);

	drawBox(-7, -4, 0, 3, 0, 3);

	glPopMatrix();

	glDisable(GL_STENCIL_TEST);
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);




	//тень на кубик справа
	glClear(GL_STENCIL_BUFFER_BIT);

	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glStencilFunc(GL_ALWAYS, 0x1, 0x1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glBegin(GL_POLYGON);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-8.0f, 0.0f, 0.0f);
	glVertex3f(-8.0f, 0.0f, -2.0f);
	glVertex3f(-8.0f, 2.0f, -2.0f);
	glVertex3f(-8.0f, 2.0f, 0.0f);
	glEnd();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 0x1, 0x1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

	glColor4f(0.0, 0.0, 0.0, 0.5);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(0.01, 0.0, 0.0);
	shadowmatrix(FloorMatrix, FloorR, l_position);

	glMultMatrixf((GLfloat*)FloorMatrix);

	drawBox(-7, -4, 0, 3, 0, 3);

	glPopMatrix();

	glDisable(GL_STENCIL_TEST);
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

}

//туман
float g_FogDensity = 0.02f;
bool g_bFog = false;//true;
void Fog()
{	
	glEnable(GL_FOG);
	float fogColor[4] = { 0.5f, 0.5f, 0.5f, 0.2f };
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_DENSITY, g_FogDensity);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 0);
	glFogf(GL_FOG_END, 10.0f);
}

//частицы
#define MAX_PARTICLES 1000          // Максимальное количество частиц

float rad_size = 3.0f;             // Размер "радиуса" потока частиц

float particle_size = 0.2f;           // Размер частицы

float xg = 1.5f;                   // Направление частицы по X
float yg = 1.5f;                   // Направление частицы по Y

float xpos = 5.0f;                  // Позиця частицы по X
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

particles particle[MAX_PARTICLES];

void Init2()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 800.0f, 600.0f, 0.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	for (loop = 0; loop < MAX_PARTICLES; loop++)
	{
		particle[loop].life = 1.0f;
		particle[loop].fade = 0.001f;               // Создаём в начале взрыв

		particle[loop].x = 0.0f + xpos;
		particle[loop].y = 0.0f + ypos;

		particle[loop].r = (float(rand() % 100) / 100.0f) + color;
		particle[loop].g = (float(rand() % 100) / 100.0f) + color;
		particle[loop].b = (float(rand() % 100) / 100.0f) + color;

		particle[loop].xi = float((rand() % 50) - xg) * 30.0f;
		particle[loop].yi = float((rand() % 50) - yg) * 30.0f;


	}
}

void DrawParticles(void)
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

			particle[loop].x =0.0f + xpos;
			particle[loop].y =0.0f + ypos;

			particle[loop].r = (float(rand() % 100) / 100.0f) + color;
			particle[loop].g = (float(rand() % 100) / 100.0f) + color;
			particle[loop].b = (float(rand() % 100) / 100.0f) + color;

			particle[loop].xi = float((rand() % 50) - xg) * rad_size;
			particle[loop].yi = float((rand() % 50) - yg) * rad_size;

		}
	}

}


void display1(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-6.0f, -6.0f, -15.0f);

	glTranslated(0, 0, -3 * ObjectSize);
	glRotated(x_angle, 1, 0, 0);
	glRotated(y_angle, 0, 1, 0);

	glEnable(GL_LIGHTING);

	// Устанавливаем источник освещения
	glLightfv(GL_LIGHT0, GL_POSITION, l_position);

	// Рисуем объекты

	glEnable(GL_DEPTH_TEST);
	ObjectsOnArea(0);
	Area();
	DownArea();
	Fog();
	

	// источник света
	GLfloat ls_emissive[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ls_emissive);
	glPushMatrix();
	glTranslatef(l_position[0], l_position[1], l_position[2]);
	glutSolidSphere(0.1, 10, 5);
	glPopMatrix();


	//нижняя плоскость
	GLfloat ds_emissive[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat ds_diffuse[4] = { 0.0f, 0.0f, 0.3f, 0.0f };
	GLfloat ds_specular[4] = { 0.2f, 0.2f, 0.6f, 0.0f };
	GLfloat ds_ambient[4] = { 0.1f, 0.1f, 0.1f, 0.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ds_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ds_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ds_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ds_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
	DownSurfase();
	// Помечаем в буфере трафарета пикселы отражающей поверхности
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_ZERO, GL_ZERO, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glDepthMask(GL_FALSE);
	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	RenderSurface(0);
	glDepthMask(GL_TRUE);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	// Рисуем отраженные объекты (только в отражающей поверхности)
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilFunc(GL_EQUAL, 1, 1);
	glPushMatrix();
	glScaled(-1, 1, 1); // Матрица отражения
	// Устанавливаем источник освещения (отраженный)
	glLightfv(GL_LIGHT0, GL_POSITION, l_position);
	ObjectsOnArea(0);
	Area();
	if ((y_angle>40)&&(y_angle<191)) Shadow();
	glPopMatrix();

	glDisable(GL_STENCIL_TEST);
	// Рисуем  поверхность
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	Area();
	glDisable(GL_POLYGON_SMOOTH);
	glDisable(GL_BLEND);
	Shadow();

	glFlush();
	glutSwapBuffers();
	
}

void display2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawParticles();
	glutPostRedisplay();
	glutSwapBuffers();
}

void display()
{
	if (SceneNumber == 1)
		display1();
	if (SceneNumber == 2)
		display2();
}
void keypress(unsigned char key, int x, int y)
{
	if (key == 27) {
		glutDestroyWindow(glutGetWindow());
		exit(1);
	}

	if (key == '1')
		SceneNumber = 1;
	if (key == '2')
		SceneNumber = 2;
	if (key == 'a') {
		xg += 0.5f;
	}

	if (key == 'd') {
		xg -= 0.5f;
	}

	if (key == 'w') {
		yg += 0.5f;
	}

	if (key == 's') {
		yg -= 0.5f;
	}

}

void mouseClick(int button, int state, int x, int y)
{
	mouse_button = button;
	mouse_state = state;
	mouse_x = x;
	mouse_y = y;
}

// Поворот объекта при движении мыши
void mouseMotion(int x, int y)
{
	int dx = x - mouse_x;
	int dy = y - mouse_y;
	if (mouse_state == GLUT_DOWN) {
		if (mouse_button == GLUT_LEFT_BUTTON) {
			y_angle += dx;
			if (y_angle < 0)
				y_angle += 360;
			if (y_angle >= 360)
				y_angle -= 360;
			x_angle += dy;
			if (x_angle < 0)
				x_angle += 360;
			if (x_angle >= 360)
				x_angle -= 360;

			display();
		}
	}
	mouse_x = x;
	mouse_y = y;

}

bool Init1()
{
	// Устанавливаем цвет
	GLfloat l_diffuse[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat l_specular[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat l_ambient[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambient);
	// Устанавливаем источник освещения
	GLfloat l_position[4] = { 10.0f ,10.0f, 10.0f, 1.0f };
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, l_position);
	// Включаем освещение
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	// Прочие настройки OpenGL
	glEnable(GL_DEPTH_TEST);

	return true;
}

bool Init()
{
	Init1();
	Init2();
	return true;
}


int main(int argc, char** argv)
{
	glutInitWindowSize(800, 600);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutCreateWindow("E.Zizganova/224 group");
	if (!Init())
		return 1;
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutDisplayFunc(display);

	glutKeyboardFunc(keypress);
	glutReshapeFunc(reshape);
	glutIdleFunc(animate);

	glutMainLoop();
	return 0;
}

