#include <GL\glut.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include <math.h>
#define PI 3.1415926
//function declare
void init();
void display(void);
void mytime(int);
void reshape(GLsizei, GLsizei);

SYSTEMTIME timenow;
float hh, mm, ss, ms;
int R = 10;
int n = 30;

using namespace std;
int main(int argc, char* argv[]) {
	
	int arg1 = 2;
	char* arg2[] = { "hello","" };
	glutInit(&arg1, arg2);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("animate test");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(10, mytime, 1);
	glutMainLoop();

	return 0;

}

void init() {
	GetLocalTime(&timenow);
	hh = timenow.wHour;
	mm = timenow.wMinute;
	ss = timenow.wSecond;
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		for (int i = 0; i < n; i++) {
			glVertex2f(R * cos(2 * i * PI / n), R * sin(2 * i * PI / n));
		}
	glEnd();
	int xc = 0, yc = 0;
	float xs, ys, xm, ym, xh, yh;
	xs = xc + R * cos(PI / 2.0 - (ss + ms / 1000.0) / 60.0 * 2 * PI);
	ys = yc + R * sin(PI / 2.0 - (ss + ms / 1000.0) / 60.0 * 2 * PI);
	xm = xc + R * cos(PI / 2.0 - (mm + ss / 60.0) / 60.0 * 2.0 * PI);
	ym = yc + R * sin(PI / 2.0 - (mm + ss / 60.0) / 60.0 * 2.0 * PI);
	xh = xc + (R - 5) * cos(PI / 2.0 - (hh + (mm + ss / 60.0) / 60.0) / 12.0 * 2.0 * PI);
	yh = yc + (R - 5) * sin(PI / 2.0 - (hh + (mm + ss / 60.0) / 60.0) / 12.0 * 2.0 * PI);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(xc, yc);
	glVertex2f(xs, ys);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(xc, yc);
	glVertex2f(xm, ym);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(xc, yc);
	glVertex2f(xh, yh);
	glEnd();

	glutSwapBuffers();
}

void mytime(int t) {
	GetLocalTime(&timenow);
	hh = timenow.wHour;
	mm = timenow.wMinute;
	ss = timenow.wSecond;
	ms = timenow.wMilliseconds;
	glutTimerFunc(10, mytime, 0);
	glutPostRedisplay();
}

void reshape(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.5 * R * w / h, 1.5 * R * w / h, -1.5 * R, 1.5 * R);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
}