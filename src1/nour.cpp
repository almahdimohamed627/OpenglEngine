#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

double th = 0;
double Ex = 0;
double Ez = 0;
double E = 0;
double r = 0;
double r2 = 0;
int oldTimeSinceStart = 0;
int timeSinceStart;
int deltaTime;
bool doorOpen = false;
bool chairTableOpen = false;

GLUquadricObj* a = gluNewQuadric();

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: /* Escape key */
		exit(0);
		break;
	case 'u':
		E++;
		break;
	case 'd':
		E--;
		break;

	case 'h':
		if (chairTableOpen)
		{
			chairTableOpen = false;
		}
		else
		{
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
	default:
		break;
	}
}

void Special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		th += 0.05;
		break;
	case GLUT_KEY_LEFT:
		th -= 0.05;
		break;
	case GLUT_KEY_UP:
		Ex = Ex + cos(th);
		Ez = Ez + sin(th);
		break;
	case GLUT_KEY_DOWN:
		Ex = Ex - cos(th);
		Ez = Ez - sin(th);
		break;
	default:
		break;
	}
}

void printFPS()
{
	timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	std::cout << 1000 / deltaTime << " " << Ex << " " << E << " " << Ez << std::endl;
}

void initChairList()
{
	glPushMatrix();
	glNewList(8, GL_COMPILE);
	glColor3ub(90, 90, 90);
	GLUquadric* a = gluNewQuadric();
	glPushMatrix();
	glTranslated(-5, 0, 0);

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslated(0.9, -5, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.4, 10, -1.7);
	glRotatef(80, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslated(-10.9, -5, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(100, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
	// handle
	glPushMatrix();
	glTranslated(0, 6, 2);
	glScaled(0.7, 0.6, 0.7);
	glPushMatrix();
	glRotatef(100, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 10);
	glRotatef(80, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glTranslated(0, 0, 10);

	glPushMatrix();
	glRotatef(80, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glTranslated(5, 0, 0);
	glPushMatrix();
	glTranslated(-1.4, 10, -1.7);
	glRotatef(80, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(100, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
	glPushMatrix();
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
	glTranslated(0, 0, 10);
	glPushMatrix();
	glRotatef(80, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 30, 30);
	glPopMatrix();
	glPopMatrix();
	// wooden stuff
	glPushMatrix();
	glColor3ub(190, 150, 51);
	glPushMatrix();
	glTranslated(0, 6, -0.4);
	glRotatef(-10, 1, 0, 0);
	glScaled(1.5, 1, 0.1);
	glutSolidCube(7);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.55, 5.5);
	glScaled(1, 0.06, 0.9);
	glutSolidCube(11);
	glPopMatrix();
	glEndList();
	// table
	glNewList(9, GL_COMPILE);
	glPushMatrix();
	glColor3ub(190, 150, 51);
	glPushMatrix();
	glTranslated(4.52, 0.5, 0);
	glScaled(1, 0.06, 0.6);
	glutSolidCube(11);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0.5, -4);
	glScaled(0.4, 0.13, 0.6);
	glutSolidCube(5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glEndList();
	glPopMatrix();
}
void drewChair()
{
	glPushMatrix();
	if (chairTableOpen)
	{
		if (r < 90)
		{
			r += deltaTime / (180.0 * 15.0);
		}
	}
	else
	{
		if (r > 0)
		{
			r -= deltaTime / (180.0 * 15.0);
		}
	}
	glPushMatrix();
	glCallList(8);
	glTranslated(-5.2, 6, 7.4);
	glRotated(r, 0, 0, 1);
	glCallList(9);
	glPopMatrix();
	glPopMatrix();
}

void initDoor()
{
	glPushMatrix();
	GLUquadric* a = gluNewQuadric();

	// doors
	glPushMatrix();
	glNewList(6, GL_COMPILE);
	glPushMatrix();
	glColor3ub(175, 125, 51);
	glTranslatef(2, 0, 0);
	glScaled(1, 2, 0.08);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(220, 186, 136);
	glTranslated(3.6, 0, -0.5);
	gluCylinder(a, 0.2, 0.2, 1, 30, 30);
	gluDisk(a, 0, 0.2, 30, 30);
	glTranslated(0, 0, 1);
	gluDisk(a, 0, 0.2, 30, 30);
	glPopMatrix();
	glEndList();
	glPopMatrix();
}

void drewDoor()
{
	if (doorOpen)
	{
		if (r2 < 90)
		{
			r2 += deltaTime / (8.0 * 15.0);
		}
	}
	else
	{
		if (r2 > 0)
		{
			r2 -= deltaTime / (8.0 * 15.0);
		}
	}
	// glRotatef(90, 1, 0, 0);

	glPushMatrix();
	glRotatef(r2, 0, 1, 0);
	glCallList(6);
	glPopMatrix();
}

void initStairs()
{
	glNewList(36, GL_COMPILE);
	glPushMatrix();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, -4);
	glVertex3f(0, 10, -4);
	glVertex3f(12, 10, -4);
	glVertex3f(12, 0, -4);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(12, 0, -4);
	glVertex3f(12, 10, -4);
	glVertex3f(12, 10, 4);
	glVertex3f(12, 0, 4);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(12, 0, 4);
	glVertex3f(12, 10, 4);
	glVertex3f(0, 10, 4);
	glVertex3f(0, 0, 4);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(8, 5, 0);
	glVertex3f(8, 7.5, 0);
	glVertex3f(0, 2.5, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2.5, 0);
	glVertex3f(0, 2.5, -0.3);
	glVertex3f(0, 0, -0.3);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(8, 5, 0);
	glVertex3f(8, 7.5, 0);
	glVertex3f(8, 7.5, -0.3);
	glVertex3f(8, 5, -0.3);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, 2.5, 0);
	glVertex3f(8, 7.5, 0);
	glVertex3f(8, 7.5, -0.3);
	glVertex3f(0, 2.5, -0.3);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -0.3);
	glVertex3f(8, 5, -0.3);
	glVertex3f(8, 7.5, -0.3);
	glVertex3f(0, 2.5, -0.3);
	glEnd();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -4);
	glVertex3f(8, 5, -4);
	glVertex3f(8, 5, 0);
	glVertex3f(0, 0, 0);
	glEnd();
	for (int i = 0; i < 10; i++)
	{
		glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_QUADS);
		glVertex3f(0, 0, -4);
		glVertex3f(0, 0.5, -4);
		glVertex3f(0, 0.5, 0);
		glVertex3f(0, 0, 0);
		glColor3f(0.4, 0.4, -0.4);
		glVertex3f(0, 0.5, -4);
		glVertex3f(0.8, 0.5, -4);
		glVertex3f(0.8, 0.5, 0);
		glVertex3f(0, 0.5, 0);
		glEnd();
		glPopMatrix();
		glTranslatef(0.8, 0.5, 0);
	}
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -4);
	glVertex3f(4, 0, -4);
	glVertex3f(4, 0, 4);
	glVertex3f(0, 0, 4);
	glEnd();
	glRotatef(180, 0, 1, 0);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(8, 5, 0);
	glVertex3f(8, 7.5, 0);
	glVertex3f(0, 2.5, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2.5, 0);
	glVertex3f(0, 2.5, -0.3);
	glVertex3f(0, 0, -0.3);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(8, 5, 0);
	glVertex3f(8, 7.5, 0);
	glVertex3f(8, 7.5, -0.3);
	glVertex3f(8, 5, -0.3);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, 2.5, 0);
	glVertex3f(8, 7.5, 0);
	glVertex3f(8, 7.5, -0.3);
	glVertex3f(0, 2.5, -0.3);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -0.3);
	glVertex3f(8, 5, -0.3);
	glVertex3f(8, 7.5, -0.3);
	glVertex3f(0, 2.5, -0.3);
	glEnd();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -4);
	glVertex3f(8, 5, -4);
	glVertex3f(8, 5, 0);
	glVertex3f(0, 0, 0);
	glEnd();
	for (int i = 0; i < 10; i++)
	{
		glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_QUADS);
		glVertex3f(0, 0, -4);
		glVertex3f(0, 0.5, -4);
		glVertex3f(0, 0.5, 0);
		glVertex3f(0, 0, 0);
		glColor3f(0.4, 0.4, -0.4);
		glVertex3f(0, 0.5, -4);
		glVertex3f(0.8, 0.5, -4);
		glVertex3f(0.8, 0.5, 0);
		glVertex3f(0, 0.5, 0);
		glEnd();
		glPopMatrix();
		glTranslatef(0.8, 0.5, 0);
	}
	glPopMatrix();
	glEndList();
}

void initsaralists()
{
	glPushMatrix();
	glNewList(1, GL_COMPILE);
	// chairs
	glPushMatrix();
	glTranslated(1, 0, 0.8);

	glPushMatrix();
	glColor3ub(0, 0, 255);
	glScaled(1, 0.1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotated(90, 1, 0, 0);
	glTranslated(0.2, 0.2, 0.2);
	glScaled(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotated(90, 1, 0, 0);
	glTranslatef(-0.2, 0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.2, -0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.2, -0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 255);
	glTranslated(0.2, 0.46, 0);
	glRotated(90, 0, 0, 1);
	glScalef(1, 0.1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslated(0.2, 0.2, -0.12);
	glScalef(0.01, 0.1, 0.4);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.2, -0.2, -0.12);
	glScalef(0.01, 0.1, 0.4);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();

	// chairs 2
	glPushMatrix();
	glTranslatef(1, 0, -0.8);

	glPushMatrix();
	glColor3ub(0, 0, 255);
	glScalef(1, 0.1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.2, 0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.2, 0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.2, -0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.2, -0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 255);
	glTranslated(0.2, 0.46, 0);
	glRotated(90, 0, 0, 1);
	glScalef(1, 0.1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslated(0.2, 0.2, -0.12);
	glScalef(0.01, 0.1, 0.4);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.2, -0.2, -0.12);
	glScalef(0.01, 0.1, 0.4);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();

	// table
	glTranslatef(0, 0.4, 0);
	glPushMatrix();

	glColor3ub(46, 128, 168);
	glScalef(1, 0.1, 1.5);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.45, 1.2, 0.45);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.45, 1.2, 0.45);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.45, -1.2, 0.45);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(195, 200, 200);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.45, -1.2, 0.45);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(1);
	glPopMatrix();
	glEndList();

	glNewList(4, GL_COMPILE);
	glPushMatrix();
	//	glTranslated(0, 18, 0);
	GLUquadric * a = gluNewQuadric();
	glColor3ub(100, 100, 100);
	// neck
	glPushMatrix();
	glTranslatef(0, -10, 1.2);
	glRotatef(-10, 1, 0, 0);
	glScalef(0.8, 2.4, 0.6);
	glutSolidCube(4);
	glPopMatrix();

	// leg
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(a, 3, 3, 12, 30, 30);
	glPopMatrix();

	glColor3ub(20, 20, 15);
	// base
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(0.6, 3.7, 100, 100);
	glPopMatrix();

	// back
	glPushMatrix();
	glRotatef(-5, 1, 0, 0);
	glScalef(1, 1.3, 0.4);
	gluSphere(a, 7, 30, 30);
	glPopMatrix();

	glColor3ub(100, 100, 100);
	// arms
	glPushMatrix();
	glTranslatef(5, -14, 4);
	glRotatef(-90, 1, -0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -14, 4);
	glRotatef(-90, 1, 0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 30, 30);
	glPopMatrix();

	glColor3ub(20, 20, 15);
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 30, 30);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 30, 30);
	glPopMatrix();
	glPopMatrix();
	glEndList();

	glNewList(5, GL_COMPILE);

	glPushMatrix();

	glScaled(2, 2.5, 3.5);

	glPushMatrix();
	glScaled(0.01, 1, 0.5);
	glColor3ub(150, 201, 226);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.5, 0);
	glScalef(0, 0.1, 0.5);
	glColor3ub(123, 123, 123);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.5, 0);
	glScalef(0, 0.1, 0.5);
	glColor3ub(123, 123, 123);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 0.26);
	glScalef(0.01, 1.06, 0.05);
	glColor3ub(123, 123, 123);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -0.26);
	glScalef(0.01, 1.06, 0.05);
	glColor3ub(123, 123, 123);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
	glEndList();

	glNewList(2, GL_COMPILE);

	glColor3ub(245, 241, 185);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();

	glColor3ub(245, 241, 185);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, 10.0f);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glEnd();

	glColor3ub(245, 241, 185);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glVertex3f(-10.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 0.0f, 10.0f);
	glEnd();

	glColor3ub(245, 241, 185);
	glBegin(GL_QUADS);
	glVertex3f(-3.0f, 0.0f, 10.0f);
	glVertex3f(-3.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();

	glColor3ub(245, 241, 185);
	glBegin(GL_QUADS);
	glVertex3f(-6.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 5.0f, 10.0f);
	glVertex3f(-3.0f, 5.0f, 10.0f);
	glVertex3f(-3.0f, 7.0f, 10.0f);
	glEnd();

	glColor3ub(245, 241, 185);
	glBegin(GL_QUADS);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();
	////////////////////////////////////////////////////////////////////////////
	glPushMatrix();
	glScalef(1, 0, 1);
	glColor3ub(130, 130, 130);
	glutSolidCube(20);
	glPopMatrix();

	glCallList(10);

	glPushMatrix();
	glTranslated(-8.8, 2, -9.9);
	glTranslated(-2.1, 0, 0);
	glRotated(90, 0, 1, 0);
	for (int i = 0; i < 10; i++)
	{
		glTranslated(0, 0, 1.9);
		glCallList(5);
	}
	glPopMatrix();

	// teacher's computer
	glPushMatrix();
	glTranslated(-8.5, 0.85, -9.5);
	glRotated(90, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	glCallList(3);

	glPopMatrix();
	glEndList();

	glNewList(10, GL_COMPILE);
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

	glPushMatrix();
	glTranslated(-9.9, 1, 0);
	glScalef(0.1, 0.1, 5.5);
	glColor3f(0, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	glEndList();

	glNewList(7, GL_COMPILE);

	glPushMatrix();
	glTranslated(-6.5, 1, -8);
	for (int i = 0; i < 5; i++)
	{
		glTranslated(3, -0.45, 0);
		glCallList(1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3.5, 1, 8);
	for (int i = 0; i < 4; i++)
	{
		glTranslated(3, -0.45, 0);
		glCallList(1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(-6.5, 1, -1);
	for (int i = 0; i < 5; i++)
	{
		glTranslated(3, -0.45, 0);
		glCallList(1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(-6.5, 1, 2);
	for (int i = 0; i < 5; i++)
	{
		glTranslated(3, -0.45, 0);
		glCallList(1);
	}
	glPopMatrix();
	glEndList();
	glNewList(3, GL_COMPILE);

	glPushMatrix();
	glTranslated(0, 0.35, 0);
	glPushMatrix();
	glTranslated(-0.25, -0.35, 0);
	glScalef(0.5, 0.1, 0.8);
	glColor3ub(0, 0, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glScalef(1, 0, 0.8);
	glColor3ub(46, 128, 168);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.4, 0);
	glRotated(90, 0, 0, 1);
	glScalef(1, 0, 0.8);
	glColor3ub(46, 128, 168);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, 0.1, 0.4);
	glRotated(90, 1, 0, 0);
	glScalef(0.5, 0, 0.8);
	glColor3ub(46, 128, 168);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, -0.5, 0.4);
	glRotated(90, 1, 0, 0);
	glScalef(0.5, 0, 0.8);
	glColor3ub(46, 128, 168);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, 0.1, -0.4);
	glRotated(90, 1, 0, 0);
	glScalef(0.5, 0, 0.8);
	glColor3ub(46, 128, 168);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, -0.5, -0.4);
	glRotated(90, 1, 0, 0);
	glScalef(0.5, 0, 0.8);
	glColor3ub(46, 128, 168);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.3, -0.2, 0.0);
	glScaled(0.0, 0.45, 0.20);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(0.5f, 0.0f, -1.0f);
	glVertex3f(0.5f, 0.5f, -1.0f);
	glVertex3f(0.5f, 0.5f, 1.0f);
	glVertex3f(0.5f, 0.0f, 1.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslated(-0.3, -0.2, 0.0);
	glRotated(90, 1, 0, 0);
	glScaled(0.2, 0.2, 0.2);
	gluCylinder(a, 0.05, 0.05, 1, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.30, -0.3, 0);
	glScalef(0.1, 0.01, 0.1);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.45, -0.3, 0);
	glScalef(0.1, 0.01, 0.4);
	glColor3ub(0, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.2, -0.65, 0.2);
	glScaled(0.2, 0.5, 0.2);
	glColor3ub(0, 0, 0);
	glRotated(90, 1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslated(0.1, -0.05, -0.8);
	glScaled(0.03, 0.03, 0.03);
	glCallList(4);
	glPopMatrix();

	glPopMatrix();
	glEndList();
	glPopMatrix();

	//////////////////////////////////////////////////عراب

	////counter
	glNewList(21, GL_COMPILE);

	glPushMatrix();

	glTranslatef(0, -0.4, 0);

	glPushMatrix();

	glRotatef(-90, 0, 1, 0);

	glPushMatrix();
	glTranslated(0, 1, 0);
	glColor3f(0.3, 0.3, 0.3);
	glScalef(2, 2, 9);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glTranslated(7.5, -2, -7);

	glColor3f(0.7, 0.8, 0.9);
	glBegin(GL_QUADS);
	glVertex3d(5.2, 5, 3);
	glVertex3d(-5.2, 5, 3);
	glVertex3d(-5.2, 5, -3);
	glVertex3d(5.2, 5, -3);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glTranslated(-7.5, -2, -7);

	glColor3f(0.7, 0.8, 0.9);
	glBegin(GL_QUADS);
	glVertex3d(5.2, 5, 3);
	glVertex3d(-5.2, 5, 3);
	glVertex3d(-5.2, 5, -3);
	glVertex3d(5.2, 5, -3);
	glEnd();
	glPopMatrix();

	////////////صراف

	glPushMatrix();
	glTranslated(0, 5, 0);
	glColor3f(0.7, 0.5, 0.6);
	glScalef(1, 0.6, 1.19);
	glutSolidCube(4);
	glPopMatrix();

	glPushMatrix();

	glTranslated(0, 4.3, 0);

	glColor3f(0.3, 0.3, 0.9);
	glBegin(GL_QUADS);
	glVertex3d(1.5, 2, 2);
	glVertex3d(-1.5, 2, 2);
	glVertex3d(-1.5, 2, -2);
	glVertex3d(1.5, 2, -2);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.7, 6, 1);
	glColor3f(0.7, 0.5, 0.6);
	glScalef(0.1, 1.5, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.6, 7, 1);
	glColor3f(0.1, 0.2, 0.6);
	glScalef(0.1, 1, 2);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();

	/////////////// coounter
	glPushMatrix();

	glTranslatef(16.5, 0, -12);

	glPushMatrix();
	glTranslated(0, 1, 0);
	glColor3f(0.3, 0.3, 0.3);
	glScalef(2, 2, 6);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glTranslated(0, -2, -7);

	glColor3f(0.7, 0.8, 0.9);
	glBegin(GL_QUADS);
	glVertex3d(8.2, 5, 3);
	glVertex3d(-8.2, 5, 3);
	glVertex3d(-8.2, 5, -3);
	glVertex3d(8.2, 5, -3);
	glEnd();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	////////////////////coca

	glPushMatrix();
	glTranslatef(5, 0.8, 15);
	glRotatef(-90, 0, 1, 0);

	glPushMatrix();
	glTranslated(0, 4.6, 0);
	glColor3f(0.3, 0.3, 0.3);
	glScalef(2, 5, 3);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glTranslated(0, -1.99, -4);
	// glScalef(1, 1, 1.8);
	glColor3f(0.4, 0.3, 0.5);
	glBegin(GL_QUADS);
	glVertex3d(4, 5, 5.5);
	glVertex3d(-4, 5, 5.5);
	glVertex3d(-4, 5, -5.5);
	glVertex3d(4, 5, -5.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3.49, 4.6, -3);
	glColor3f(0.3, 0.4, 0.6);
	glScalef(0.1, 2, 0.2);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3, 6, -3);
	glColor3f(0.3, 0.9, 0.6);
	glScalef(1, 0.2, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3, 3, -3);
	glColor3f(0.3, 0.9, 0.6);
	glScalef(1, 0.2, 0.2);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glEndList();

	////table
	glNewList(22, GL_COMPILE);

	glPushMatrix();

	glScalef(0.8, 0.8, 0.8);
	glRotatef(90, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 2.5, 0);
	glColor3f(0.9, 0.3, 0.3);
	glScalef(1.2, 0.1, 3);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5, 2.7, 6.6);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(1.3, 2.7, 3.8);
	gluCylinder(a, 0.19, 0.19, 1.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5, 2.7, -6.6);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(1.3, 2.7, 3.8);
	gluCylinder(a, 0.19, 0.19, 1.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.5, 2.7, -6.6);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(1.3, 2.7, 3.8);
	gluCylinder(a, 0.19, 0.19, 1.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.5, 2.7, 6.6);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(1.3, 2.7, 3.8);
	gluCylinder(a, 0.19, 0.19, 1.5, 10, 10);
	glPopMatrix();

	glPopMatrix();

	glEndList();

	//// chair

	glNewList(23, GL_COMPILE);

	glPushMatrix();
	glTranslatef(-20, 2, 5);
	glRotatef(90, 0, 1, 0);
	glScalef(0.9, 0.9, 0.9);
	glPushMatrix();
	glTranslatef(0.2, 0.5, 0);
	glColor3f(0.6, 0.1, 0.3);
	glScalef(1.2, 0.2, 0.8);
	gluSphere(a, 2, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2, 1.5, 0.5);
	glColor3f(0.3, 0.3, 0.3);
	glScalef(0.1, 2, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2, 1.5, -0.5);
	glColor3f(0.3, 0.3, 0.3);
	glScalef(0.1, 2, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.5, 3.2, 0);
	glColor3f(0.6, 0.1, 0.3);
	glScalef(0.8, 1.9, 1.6);
	gluSphere(a, 1.1, 10, 10);
	glPopMatrix();
	///////////////////

	glPushMatrix();
	glTranslated(1.5, 0.6, 0.69);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(0.8, 1, 2.3);
	gluCylinder(a, 0.19, 0.19, 1.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.5, 0.6, -0.69);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(0.8, 1, 2.3);
	gluCylinder(a, 0.19, 0.19, 1.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.9, 0.6, -0.69);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(0.8, 1, 2.3);
	gluCylinder(a, 0.19, 0.19, 1.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.9, 0.6, 0.69);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(0.8, 1, 2.3);
	gluCylinder(a, 0.19, 0.19, 1.5, 10, 10);
	glPopMatrix();
	glPopMatrix();
	glEndList();

	/////////////////////////////////////////////////////عراب
	glNewList(20, GL_COMPILE);

	// call  counter
	glPushMatrix();
	glTranslatef(5, 0, -3);
	for (int i = 0; i < 1; i++)
	{

		glCallList(21);
	}
	glPopMatrix();
	////////
	glPushMatrix();
	glTranslatef(0, 0, -15);
	// call   table
	glPushMatrix();

	glTranslated(-30, 0, -60);
	for (int i = 0; i < 2; i++)
	{
		glTranslated(0, 0, 45);
		glCallList(22);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslated(-45, 0, -22);
	for (int i = 0; i < 2; i++)
	{
		glTranslated(0, 0, 20);
		glCallList(22);
	}

	glPopMatrix();

	glPushMatrix();
	glTranslated(-60, 0, -38);
	for (int i = 0; i < 3; i++)
	{
		glTranslated(0, 0, 23);
		glCallList(22);
	}

	glPopMatrix();

	/// call chair
	glPushMatrix();

	glTranslated(-8, -2, -70);
	for (int i = 0; i < 2; i++)
	{
		glTranslated(0, 0, 45);
		glCallList(23);
	}
	glPopMatrix();

	glPushMatrix();

	glTranslated(-12, -2, -70);
	for (int i = 0; i < 2; i++)
	{
		glTranslated(0, 0, 45);
		glCallList(23);
	}
	glPopMatrix();

	glPushMatrix();

	glTranslated(-48, -2, 83);
	glRotatef(180, 0, 1, 0);
	for (int i = 0; i < 2; i++)
	{

		glTranslated(0, 0, 45);
		glCallList(23);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslated(-53, -2, 83);
	glRotatef(180, 0, 1, 0);
	for (int i = 0; i < 2; i++)
	{

		glTranslated(0, 0, 45);
		glCallList(23);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslated(-82, -2, 63);
	glRotatef(180, 0, 1, 0);
	for (int i = 0; i < 3; i++)
	{

		glTranslated(0, 0, 23);
		glCallList(23);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslated(-78, -2, 63);
	glRotatef(180, 0, 1, 0);
	for (int i = 0; i < 3; i++)
	{

		glTranslated(0, 0, 23);
		glCallList(23);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslated(-42, -2, -46);
	for (int i = 0; i < 3; i++)
	{
		glTranslated(0, 0, 23);
		glCallList(23);
	}
	glPopMatrix();

	glPushMatrix();

	glTranslated(-38, -2, -46);
	for (int i = 0; i < 3; i++)
	{
		glTranslated(0, 0, 23);
		glCallList(23);
	}
	glPopMatrix();

	glPushMatrix();

	glTranslated(-27, -2, -30);
	for (int i = 0; i < 2; i++)
	{
		glTranslated(0, 0, 20);
		glCallList(23);
	}
	glPopMatrix();

	glPushMatrix();

	glTranslated(-23, -2, -30);
	for (int i = 0; i < 2; i++)
	{
		glTranslated(0, 0, 20);
		glCallList(23);
	}
	glPopMatrix();

	glPushMatrix();

	glTranslated(-68, -2, 45);
	glRotatef(180, 0, 1, 0);
	for (int i = 0; i < 2; i++)
	{

		glTranslated(0, 0, 20);
		glCallList(23);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslated(-63, -2, 45);
	glRotatef(180, 0, 1, 0);
	for (int i = 0; i < 2; i++)
	{

		glTranslated(0, 0, 20);
		glCallList(23);
	}
	glPopMatrix();
	glPopMatrix();

	glEndList();
	///////////حيطان عراب
	glNewList(24, GL_COMPILE);
	glPushMatrix();

	glColor3ub(245, 241, 185);
	glTranslatef(250, 0, 17);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -50.0f);
	glVertex3f(-10.0f, 38.5f, -50.0f);
	glVertex3f(50.0f, 38.5f, -50.0f);
	glVertex3f(50.0f, 0.0f, -50.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(220, 0, -53);
	glBegin(GL_QUADS);
	glVertex3f(20.0f, 0.0f, -20.0f);
	glVertex3f(20.0f, 38.5f, -20.0f);
	glVertex3f(20.0f, 38.5f, 20.0f);
	glVertex3f(20.0f, 0.0f, 20.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(240, 0, -72.8);
	glBegin(GL_QUADS);
	glVertex3f(-9.0f, 0.0f, -0.08f);
	glVertex3f(-9.0f, 38.5f, -0.08f);
	glVertex3f(0.08f, 38.5f, -0.08f);
	glVertex3f(0.08f, 0.0f, -0.08f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(211, 0, -127.3);

	glBegin(GL_QUADS);
	glVertex3f(23.0f, 0.0f, -23.0f);
	glVertex3f(23.0f, 38.5f, -23.0f);
	glVertex3f(23.0f, 38.5f, 23.0f);
	glVertex3f(23.0f, 0.0f, 23.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(223, 0, -80.6);
	glBegin(GL_QUADS);
	glVertex3f(8.0f, 0.0f, -8.0f);
	glVertex3f(8.0f, 38.5f, -8.0f);
	glVertex3f(8.0f, 38.5f, 8.0f);
	glVertex3f(8.0f, 0.0f, 8.0f);
	glEnd();
	glPopMatrix();

	glEndList();
}

void InitGL(void)
{
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	// glClearColor(1.0f, 1.0f, 1.0f, 0.5f);				// Black Background
	// glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);
	// glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	GLfloat am[] = { 0, 0, 0, 0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, am);
	GLfloat di[] = { 1, 1, 1, 0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, di);
	GLfloat sp[] = { 1, 1, 1, 0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, sp);			   // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	initChairList();
	initDoor();
	initsaralists();
	initStairs();
}

void ReSizeGLScene(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 1000.0f);
	// gluOrtho2D(0, 100, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void DrawGLScene(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat position[] = { 200, 100, 100, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	gluLookAt(Ex, E, Ez, Ex + cos(th), E, Ez + sin(th), 0, 1, 0);
	GLUquadricObj * a = gluNewQuadric();

	/////////////////////////////////////////////////////////////////

	//fist staircase
	glColor3ub(245, 241, 185);
	glPushMatrix();
	glTranslatef(367, 0, -145);
	glRotatef(90, 0, 1, 0);
	glScalef(3.85, 3.85, 3.85);
	glCallList(36);
	glPopMatrix();

	// ارض ط1 كامله
	glPushMatrix();
	glScaled(50, 5.5, 15);
	glTranslated(-1, 0, 0.37);
	glPushMatrix();
	glScalef(0.65, 0, 1);
	glTranslated(5.4, 0, 0);
	glColor3ub(130, 130, 130);
	glutSolidCube(20);
	glPopMatrix();

	// حيط يسار كل كليه
	glColor3ub(245, 241, 185);
	glBegin(GL_QUADS);
	glVertex3f(-3.0f, 0.0f, 10.0f);
	glVertex3f(-3.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////////////
	// للقسم قاعات

	glScaled(5.5, 5.5, 5.5);
	glTranslated(-26.3, 0, -16.3);
	glPushMatrix();
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		glScaled(0.76, 0.63, 0.55);
		glTranslated(-7.9, 4, 18.2);
		drewDoor();
		glPopMatrix();

		glCallList(2);
		glCallList(7);
		glTranslated(20, 0, 0);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslated(60, 0, 34.5);
	glRotated(180, 0, 1, 0);
	glPushMatrix();
	glPushMatrix();
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		glScaled(0.76, 0.63, 0.55);
		glTranslated(-7.9, 4, 18.2);
		drewDoor();
		glPopMatrix();
		glCallList(2);

		glPushMatrix();

		glPushMatrix();

		for (int j = 0; j < 7; j++)
		{
			glPushMatrix();
			glTranslatef(-3.5, 0.9, -8.5);
			glRotatef(-90, 0, 1, 0);
			glScalef(0.09, 0.09, 0.09);
			drewChair();
			glPopMatrix();
			glTranslated(2, 0, 0);
		}

		glPopMatrix();

		glPushMatrix();
		for (int j = 0; j < 7; j++)
		{
			glPushMatrix();
			glTranslatef(-3.5, 0.9, -6.5);
			glRotatef(-90, 0, 1, 0);
			glScalef(0.09, 0.09, 0.09);
			drewChair();
			glPopMatrix();
			glTranslated(2, 0, 0);
		}
		glPopMatrix();

		glPushMatrix();
		for (int j = 0; j < 5; j++)
		{
			glPushMatrix();
			glTranslatef(-0.5, 0.9, 8.5);
			glRotatef(-90, 0, 1, 0);
			glScalef(0.09, 0.09, 0.09);
			drewChair();
			glPopMatrix();
			glTranslated(2, 0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		for (int j = 0; j < 5; j++)
		{
			glPushMatrix();
			glTranslatef(-0.5, 0.9, 6.5);
			glRotatef(-90, 0, 1, 0);
			glScalef(0.09, 0.09, 0.09);
			drewChair();
			glPopMatrix();
			glTranslated(2, 0, 0);
		}
		glPopMatrix();

		glPushMatrix();
		for (int j = 0; j < 7; j++)
		{
			glPushMatrix();
			glTranslatef(-3.5, 0.9, -2.5);
			glRotatef(-90, 0, 1, 0);
			glScalef(0.09, 0.09, 0.09);
			drewChair();
			glPopMatrix();
			glTranslated(2, 0, 0);
		}
		glPopMatrix();

		glPushMatrix();
		for (int j = 0; j < 7; j++)
		{
			glPushMatrix();
			glTranslatef(-3.5, 0.9, 0.0);
			glRotatef(-90, 0, 1, 0);
			glScalef(0.09, 0.09, 0.09);
			drewChair();
			glPopMatrix();
			glTranslated(2, 0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		for (int j = 0; j < 7; j++)
		{
			glPushMatrix();
			glTranslatef(-3.5, 0.9, 2.5);
			glRotatef(-90, 0, 1, 0);
			glScalef(0.09, 0.09, 0.09);
			drewChair();
			glPopMatrix();
			glTranslated(2, 0, 0);
		}
		glPopMatrix();

		glPopMatrix();

		glTranslated(20, 0, 0);
	}
	glPopMatrix();
	
		glLoadIdentity();

		gluLookAt(Ex, E, Ez, Ex + cos(th), E, Ez + sin(th), 0, 1, 0);
		// lab
		glPushMatrix();
		glTranslated(-50, 38.49, 5);
		glScaled(50, 5.5, 15);

		glPushMatrix();
		glScalef(0.65, 0, 1);
		glTranslated(5.4, 0, 0);
		glColor3ub(130, 130, 130);
		glutSolidCube(20);
		glPopMatrix();
/*
		glColor3ub(245, 141, 285);
		glBegin(GL_QUADS);
		glVertex3f(-3.0f, 0.0f, -10.0f);
		glVertex3f(-3.0f, 7.0f, -10.0f);
		glVertex3f(10.0f, 7.0f, -10.0f);
		glVertex3f(10.0f, 0.0f, -10.0f);
		glEnd();
		*/
		glColor3ub(245, 241, 185);
		glBegin(GL_QUADS);
		glVertex3f(-3.0f, 0.0f, 10.0f);
		glVertex3f(-3.0f, 7.0f, 10.0f);
		glVertex3f(10.0f, 7.0f, 10.0f);
		glVertex3f(10.0f, 0.0f, 10.0f);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glScaled(5.5, 5.5, 5.5);
		glTranslated(-46.3, 7, -16.4);
		for (int i = 0; i < 4; i++)
		{

			glTranslated(20, 0, 0);
			glPushMatrix();
			glCallList(2);
			glPushMatrix();
			glScaled(0.76, 0.63, 0.55);
			glTranslated(-7.9, 4, 18.2);
			drewDoor();
			glPopMatrix();
			glTranslated(-6, 0.9, -9.8);
			glRotated(90, 0, 1, 0);
			glScaled(1.5, 1.5, 1.5);
			glPushMatrix();
			for (int i = 0; i < 12; i++)
			{

				glCallList(3);
				glTranslated(0, 0, 0.9);
			}
			glPopMatrix();

			glTranslated(-2, 0., 10.5);
			glPushMatrix();
			glRotated(-90, 0, 1, 0);
			for (int i = 0; i < 12; i++)
			{

				glCallList(3);
				glTranslated(0, 0, 0.9);
			}
			glPopMatrix();

			glTranslated(-11, 0.0, -1.5);
			glPushMatrix();
			glRotated(180, 0, 1, 0);
			for (int i = 0; i < 7; i++)
			{

				glCallList(3);
				glTranslated(0, 0, 0.9);
			}
			glPopMatrix();

			glPopMatrix();
		}
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();

		glTranslated(-20, 7, 0);
		for (int i = 0; i < 4; i++)
		{
			glTranslated(20, 0, 0);
			glPushMatrix();
			glCallList(2);
			glPushMatrix();
			glScaled(0.76, 0.63, 0.55);
			glTranslated(-7.9, 4, 18.2);
			drewDoor();
			glPopMatrix();
			glTranslated(-6, 0.9, -9.8);
			glRotated(90, 0, 1, 0);
			glScaled(1.5, 1.5, 1.5);
			glPushMatrix();
			for (int i = 0; i < 12; i++)
			{
				glCallList(3);
				glTranslated(0, 0, 0.9);
			}
			glPopMatrix();

			glTranslated(-2, 0., 10.5);
			glPushMatrix();
			glRotated(-90, 0, 1, 0);
			for (int i = 0; i < 12; i++)
			{

				glCallList(3);
				glTranslated(0, 0, 0.9);
			}
			glPopMatrix();

			glTranslated(-11, 0.0, -1.5);
			glPushMatrix();
			glRotated(180, 0, 1, 0);
			for (int i = 0; i < 7; i++)
			{

				glCallList(3);
				glTranslated(0, 0, 0.9);
			}
			glPopMatrix();

			glPopMatrix();
		}

		glPopMatrix();
		glPopMatrix();
		
	glLoadIdentity();
	gluLookAt(Ex, E, Ez, Ex + cos(th), E, Ez + sin(th), 0, 1, 0);

	// المدخل

	/*

		glPushMatrix();
		glColor3ub(245, 241, 185);
		glTranslatef(250.40,0,-94.4);
		glBegin(GL_QUADS);
		glVertex3f(-10.0f, 0.0f, -50.0f);
		glVertex3f(-10.0f, 38.5f, -50.0f);
		glVertex3f(50.0f, 38.5f, -50.0f);
		glVertex3f(50.0f, 0.0f, -50.0f);
		glEnd();
		glPopMatrix();
		*/
		/*
		glColor3ub(245, 241, 185);
		glBegin(GL_QUADS);
		glVertex3f(-3.0f, 0.0f, 10.0f);
		glVertex3f(-3.0f, 7.0f, 10.0f);
		glVertex3f(10.0f, 7.0f, 10.0f);
		glVertex3f(10.0f, 0.0f, 10.0f);
		glEnd();

		glColor3ub(245, 241, 185);
		glBegin(GL_QUADS);
		glVertex3f(10.0f, 0.0f, -10.0f);
		glVertex3f(10.0f, 7.0f, -10.0f);
		glVertex3f(10.0f, 7.0f, 10.0f);
		glVertex3f(10.0f, 0.0f, 10.0f);
		glEnd();
		glPopMatrix();
		*/
		// glPopMatrix();
		// glPopMatrix();
		////حيط الباب
	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(250.39, 0, -104.3);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -40.0f);
	glVertex3f(-10.0f, 38.5f, -40.0f);
	glVertex3f(40.0f, 38.5f, -40.0f);
	glVertex3f(40.0f, 0.0f, -40.0f);
	glEnd();
	glPopMatrix();
	/*
	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(336.49, 0, -29.5);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -115.0f);
	glVertex3f(-10.0f, 38.5f, -115.0f);
	glVertex3f(115.0f, 38.5f, -115.0f);
	glVertex3f(115.0f, 0.0f, -115.0f);
	glEnd();
	glPopMatrix();
	*/
	//////حيط عراب
	/*
	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(300, 0, 5.6);
	glBegin(GL_QUADS);
	glVertex3f(150.0f, 0.0f, -150.0f);
	glVertex3f(150.0f, 38.5f, -150.0f);
	glVertex3f(150.0f, 38.5f, 150.0f);
	glVertex3f(150.0f, 0.0f, 150.0f);
	glEnd();
	glPopMatrix();
	*/
	////////////////////عراب
	/*
	glPushMatrix();
	glRotated(270, 0, 1, 0);
	glTranslatef(-70, 2.5, -410);
	for (int i = 0; i < 1; i++)
	{
		glCallList(20);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(149, 0, 6);
	for (int i = 0; i < 1; i++)
	{
		glCallList(24);
	}
	glPopMatrix();
	*/
	printFPS();
	glFlush();
}

void Timer(int)
{
	glutTimerFunc(16, Timer, 0);
	glutPostRedisplay();
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
	glutReshapeFunc(ReSizeGLScene);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(Special);

	Timer(0);
	glutDisplayFunc(DrawGLScene);
	setupprojection();
	glutMainLoop();
	return 0;
}