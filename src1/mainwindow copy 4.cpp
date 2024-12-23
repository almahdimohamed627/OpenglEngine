#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include <iostream>

int k = 0;
int b = 0;
int w = 0;
int a = 0;
int s = 0;
int d = 0;
int oldTimeSinceStart = 0;
int timeSinceStart;
int deltaTime;

double r = 0;
double r2 = 0;
bool chairTableOpen = false;
bool doorOpen = false;
double t = -3.14 / 2;
float camx = 0.0f, camy = 0.0f, camz = 0.0f;
float camyaw = 0.0f;
float campitch = 0.0f;
int x_last = 0;
int y_last = 0;

void moveCam(float speed) 
{
	float x = speed * sin(camyaw);
	float z = speed * cos(camyaw);
	camx += x;
	camz += z;
}

void strafeCam(float speed) {
	float x = speed * sin(camyaw - 90.0f);
	float z = speed * cos(camyaw - 90.0f);
	camx += x;
	camz += z;
}

void lookCam(int x, int y) {
	camyaw+=x;
	campitch+=y;
	if(campitch>89.0f)
		campitch = 89.0f;
	if(campitch<-89.0f)
		campitch = -89.0f;
}

void updateCam() {
	glRotatef(-campitch, 1.0f, 0.0f, 0.0f);
	glRotatef(-camyaw, 0.0f, 1.0f, 0.0f);
	glTranslatef(-camx, -camy, -camz);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: /* Escape key */
		exit(0);
		break;
	case 'w':
		moveCam(0.1f);
		break;
	case 's':
		moveCam(-0.1f);
		break;
	case 'a':
		strafeCam(-0.1f);
		break;
	case 'd':
		strafeCam(0.1f);
		break;
	case 'q':
		camyaw += 1.0f;
		break;
	case 'e':
		camyaw -= 1.0f;
		break;
	case 'h':
		if(chairTableOpen) {
			chairTableOpen = false;
		}
		else{
			chairTableOpen = true;
		}
		break;
	case 'y':
		if (doorOpen)
		{
			doorOpen = false;
		}
		else
		{
			doorOpen = true;
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y) {
	if(state==GLUT_DOWN || 1) {
		x = x_last;
		y = y_last;
	}
}

void motion(int x, int y) {
	int x_delta = x - x_last;
	int y_delta = y - y_last;

	lookCam(x_delta, y_delta);

	x_last = x;
	y_last = y;

	glutPostRedisplay();
}
void initChairList() {
	glPushMatrix();
	glNewList(2, GL_COMPILE);
	glColor3ub(0, 150, 100);
	GLUquadric *a = gluNewQuadric();
	glPushMatrix();
	glTranslatef(-5, 0, 0);

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0.9, -5, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.4, 10, -1.7);
	glRotatef(80, 1, -0.1, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-10.9, -5, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(100, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
//handle
	glPushMatrix();
	glTranslatef(0, 6, 2);
	glScalef(0.7, 0.6,0.7);
	glPushMatrix();
	glRotatef(100, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 10);
	glRotatef(80, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glTranslatef(0, 0, 10);

	glPushMatrix();
	glRotatef(80, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPopMatrix();




	glPushMatrix();
	glTranslatef(5, 0, 0);
	glPushMatrix();
	glTranslatef(-1.4, 10, -1.7);
	glRotatef(80, 1, 0.1, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(100, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
	glPushMatrix();
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
	glTranslatef(0, 0, 10);
	glPushMatrix();
	glRotatef(80, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
	glPopMatrix();
//wooden stuff
	glPushMatrix();
	glColor3ub(110, 100, 20);
	glPushMatrix();
	glTranslatef(0, 6, -0.4);
	glRotatef(-10, 1, 0, 0);
	glScalef(1.5, 1, 0.1);
	glutSolidCube(7);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0.55, 5.5);
	glScalef(1, 0.06, 0.9);
	glutSolidCube(11);
	glPopMatrix();
	glEndList();
	// table
	glNewList(3, GL_COMPILE);
	glPushMatrix();
	glColor3ub(110, 100, 20);
	glPushMatrix();
	glTranslatef(4.52, 0.5, 0);
	glScalef(1, 0.06, 0.6);
	glutSolidCube(11);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.5, -4);
	glScalef(0.4, 0.13, 0.6);
	glutSolidCube(5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glEndList();
	glPopMatrix();
	
}
void drewChair() {
	glPushMatrix();
	if (chairTableOpen)
	{
	if (r < 90)
	{
		r += deltaTime/150.0;
	}
	}
	else {
		if(r> 0) {
			r -= deltaTime/150.0;
		}
	}
	glCallList(2);
	glTranslatef(-5.2, 6, 7.4);
	glRotatef(r, 0, 0, 1);
	glCallList(3);
	glPopMatrix();
}
void initMeetingChair() {
	glPushMatrix();
	glNewList(4, GL_COMPILE);
	GLUquadric *a = gluNewQuadric();
	glColor3ub(100, 100, 100);
	// neck
	glPushMatrix();
	glTranslatef(0, -10, 1.2);
	glRotatef(-10, 1, 0, 0);
	glScalef(0.8, 2.4, 0.6);
	glutSolidCube(4);
	glPopMatrix();

	//leg
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(a, 3, 3, 12, 100, 100);
	glPopMatrix();

	

	glColor3ub(20, 20, 15);
	//base
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(0.6, 3.7, 100, 100);
	glPopMatrix();

	//back
	glPushMatrix();
	glRotatef(-5, 1, 0, 0);
	glScalef(1, 1.3, 0.4);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glColor3ub(100, 100, 100);
	// arms
	glPushMatrix();
	glTranslatef(5, -14, 4);
	glRotatef(-90, 1, -0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -14, 4);
	glRotatef(-90, 1, 0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 100, 100);
	glPopMatrix();

	glColor3ub(20, 20, 15);
	//handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	//seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	

	glEndList();
	glPopMatrix();
}
void initMeetingTable() {
	glPushMatrix();
	glNewList(5, GL_COMPILE);
	GLUquadric *a = gluNewQuadric();
	glColor3ub(60, 45, 15);

	//table
	glPushMatrix();
	glScalef(1.5, 0.1, 1);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();

	//leg
	glPushMatrix();
	glTranslatef(0, -1, 0);
	glScalef(0.5, 5, 0.5);
	glPushMatrix();
	glScalef(1.5, 0.1, 1);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPopMatrix();

	// base
	glPushMatrix();
	glTranslatef(0, -2, 0);
	glScalef(0.7, 0.5, 0.7);
	glPushMatrix();
	glScalef(1.5, 0.1, 1);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPopMatrix();

	//square
	glColor3ub(30, 30, 30);
	glPushMatrix();
	glTranslatef(0, 0.08, 0);
	glScalef(1.5, 0.1, 1);
	glutSolidCube(3);
	glPopMatrix();

	glEndList();
	glPopMatrix();
}
void drewMeetingTable() {
	GLUquadric *a = gluNewQuadric();
	glColor3ub(250, 0, 0);
	glPushMatrix();
	glTranslatef(0, 28.5, -30);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(30, 28.5, -28);
	glRotatef(-10, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-31, 28.5, -29);
	glRotatef(10, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	
	glPushMatrix();
	glTranslatef(60, 28.5, 1);
	glRotatef(-90, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-60, 28.5, 0);
	glRotatef(90, 0, 1, 0);
	glCallList(4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 21, 0);
	glScalef(10, 10, 10);
	glCallList(5);
	glPopMatrix();
	glTranslatef(0, 28.5, 30);
	glRotatef(180, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(30, 28.5, 28);
	glRotatef(191, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-31, 28.5, 29);
	glRotatef(170, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
}
void initDoor() {
	glPushMatrix();
	GLUquadric *a = gluNewQuadric();
	

	// doors
	glPushMatrix();
	glNewList(7, GL_COMPILE);
	glPushMatrix();
	glColor3ub(110, 100, 20);
	glTranslatef(2, 0, 0);
	glScalef(1, 2, 0.08);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(110, 110, 110);
	glTranslatef(3.6, 0, -0.5);
	gluCylinder(a, 0.2, 0.2, 1, 100, 100);
	gluDisk(a, 0, 0.2, 100, 100);
	glTranslatef(0, 0, 1);
	gluDisk(a, 0, 0.2, 100, 100);
	glPopMatrix();
	glEndList();
	glPopMatrix();
}	

void drewDoor() {
	if (doorOpen)
	{
		if (r2 < 90)
		{
			r2 += deltaTime/8;
		}
	}
	else
	{
		if (r2 > 0)
		{
			r2 -= deltaTime/8;
		}
	}
	//glRotatef(90, 1, 0, 0);
	
	glPushMatrix();
	glRotatef(r2, 0, 1, 0);
	glCallList(7);
	glPopMatrix();
	
}

void initFCRoom() {
	glPushMatrix();
	glNewList(11, GL_COMPILE);
	// wall
	// اليسار تبع الشباك
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();

	// wall
	//  الحيط تبع اللوح
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, 10.0f);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glEnd();

	//اللوح
	glPushMatrix();
	glTranslated(-6.9, 1, 0);
	glBegin(GL_QUADS);
	glColor3f(250, 100, 45);
	glVertex3f(-3.0f, 0.0f, -3.0f);
	glVertex3f(-3.0f, 3.0f, -3.0f);
	glVertex3f(-3.0f, 3.0f, 3.0f);
	glVertex3f(-3.0f, 0.0f, 3.0f);
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glTranslated(-9.9, 1, 0);
	glScalef(0.1, 0.1, 5.5);
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	// الحيط تبع الباب من جهة اللوح
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glVertex3f(-10.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 0.0f, 10.0f);
	glEnd();
	//	الحيط تبع الباب من جهة تانية
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(-3.0f, 0.0f, 10.0f);
	glVertex3f(-3.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();
	// الحيط فوق الباب
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(-6.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 5.0f, 10.0f);
	glVertex3f(-3.0f, 5.0f, 10.0f);
	glVertex3f(-3.0f, 7.0f, 10.0f);
	glEnd();
	// // حواف الباب
	// glColor3f(0.4f, 0.2f, 0.0f);
	// glLineWidth(30.0f);
	// glBegin(GL_LINES);
	// glVertex3f(-6.0f, 5.0f, 10.01f);
	// glVertex3f(-3.0f, 5.0f, 10.01f);
	// glEnd();

	// glBegin(GL_LINES);
	// glVertex3f(-6.0f, 5.0f, 10.01f);
	// glVertex3f(-6.0f, 0.0f, 10.01f);
	// glEnd();

	// glBegin(GL_LINES);
	// glVertex3f(-3.0f, 0.0f, 10.01f);
	// glVertex3f(-3.0f, 5.0f, 10.01f);
	// glEnd();

	// الحيط يلي بالصدر
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();
	glEndList();
	glPopMatrix();
}

void drewFCRoom() {
	glPushMatrix();
	glCallList(11);
	glTranslatef(-6, 2, 10);
	glScalef(0.75, 0.75, 0.75);
	drewDoor();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-2.5, 0, -7.5);
	for (int i = 0; i < 6; i++)
	{
		glPushMatrix();

		for (int j = 0; j < 6; j++)
		{

			glPushMatrix();
			glTranslatef(0, 1, 0);
			glRotatef(-90, 0, 1, 0);
			glScalef(0.1, 0.1, 0.1);
			drewChair();
			glPopMatrix();
			glTranslatef(0, 0, 3);
		}

		glPopMatrix();
		glTranslatef(2.4, 0, 0);
	}
	glPopMatrix();
}

void drewStairs() {
	for (int i = 0; i < 7; i++) {
		glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		//glutSolidCube(5);
		glBegin(GL_QUAD_STRIP);	
		glVertex3f(0, 1, 0);
		glVertex3f(0, 1, 4);
		glVertex3f(1, 1, 0);
		glVertex3f(1, 1, 4);
		glColor3f(0.4, 0.4, 0.4);
		glVertex3f(1, 1.5, 0);
		glVertex3f(1, 1.5, 4);
		glVertex3f(2, 1.5, 0);
		glVertex3f(2, 1.5, 4);
		glEnd();
		glPopMatrix();
		glTranslatef(1, 0.5, 0);
	}
}

void printFPS() {
	timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	std::cout << 1000/deltaTime << std::endl;
}

void InitGL(void)
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	//glClearColor(1.0f, 1.0f, 1.0f, 0.5f);				// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat am[] = {1, 0, 0, 0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, am);
	GLfloat di[] = {0, 1, 1, 0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, di);
	GLfloat sp[] = {0, 0, 1, 0};
	glLightfv(GL_LIGHT0, GL_SPECULAR, sp);				// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	initChairList();
	initMeetingChair();
	initMeetingTable();
	initDoor();
	initFCRoom();
}
void ReSizeGLScene(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 1000.0f);
	//gluOrtho2D(0, 100, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void animation(int) {
	glutPostRedisplay();
	glutTimerFunc(16, animation, 0);
	//k++;
}
void DrawGLScene(void)

{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	updateCam();

	GLfloat position[] = {200, 100, 100, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	GLUquadricObj * a = gluNewQuadric();
	
	//gluLookAt(d, s, w, d + cos(t), s, w + sin(t), 0, 1, 0);
	//glRotatef(90, 1, 0, 0);
	glPushMatrix();
	for (int i = 0; i < 1; i++ ) {
		drewFCRoom();
		glTranslatef(20, 0, 0);
	}


	glPopMatrix();
	printFPS();

	glFlush();
}
void setupprojection()
{
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	float aspect = (float)w / (float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspect, 1.0, 100.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH); // Use single display buffer.
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("EMPTY WINDOW");
	InitGL();
	//glutReshapeFunc(ReSizeGLScene);
	
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	animation(0);
	glutDisplayFunc(DrawGLScene);
	setupprojection();
	glutMainLoop();
	return 0;
}
