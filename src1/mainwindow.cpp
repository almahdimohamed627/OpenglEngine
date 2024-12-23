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
bool sprinting = false;
bool phisics = true;
double acciliration = -0.5;
double velocity = 0;

GLUquadricObj *a = gluNewQuadric();

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: /* Escape key */
		exit(0);
		break;
	case 'q':
		if (!phisics)
			E++;
		break;
	case 'z':
		if (!phisics)
			E--;
		break;
	case 'p':
		if (phisics)
			phisics = false;
		else
			phisics = true;
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
		break;
	case 32: // space key
		if (velocity < 0.00000000001 && velocity > -0.00000000001)
		{
			velocity += 3.18937447584;
		}
		break;
	case 'd':
		th += 0.05;
		break;
	case 'a':
		th -= 0.05;
		break;
	case 'w':
		if (sprinting)
		{
			Ex = Ex + 5 * cos(th);
			Ez = Ez + 5 * sin(th);
		}
		else
		{
			Ex = Ex + 2 * cos(th);
			Ez = Ez + 2 * sin(th);
		}
		break;
	case 's':
		if (sprinting)
		{
			Ex = Ex - 5 * cos(th);
			Ez = Ez - 5 * sin(th);
		}
		else
		{
			Ex = Ex - 2 * cos(th);
			Ez = Ez - 2 * sin(th);
		}
		break;
	default:
		break;
	}
}
void initMeetingChair()
{
	glPushMatrix();
	glNewList(99, GL_COMPILE);
	GLUquadric *a = gluNewQuadric();
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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glEndList();
	glPopMatrix();
}
void initMeetingTable()
{
	glPushMatrix();
	glNewList(5, GL_COMPILE);
	GLUquadric *a = gluNewQuadric();
	glColor3ub(60, 45, 15);

	// table
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

	// leg
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

	// square
	glColor3ub(30, 30, 30);
	glPushMatrix();
	glTranslatef(0, 0.08, 0);
	glScalef(1.5, 0.1, 1);
	glutSolidCube(3);
	glPopMatrix();

	glEndList();
	glPopMatrix();
}
void drewMeetingTable()
{
	GLUquadric *a = gluNewQuadric();
	glColor3ub(250, 0, 0);
	glPushMatrix();
	glTranslatef(0, 28.5, -30);
	glCallList(99);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(30, 28.5, -28);
	glRotatef(-10, 0, 1, 0);
	glCallList(99);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-31, 28.5, -29);
	glRotatef(10, 0, 1, 0);
	glCallList(99);
	glPopMatrix();
	glPushMatrix();

	glPushMatrix();
	glTranslatef(60, 28.5, 1);
	glRotatef(-90, 0, 1, 0);
	glCallList(99);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-60, 28.5, 0);
	glRotatef(90, 0, 1, 0);
	glCallList(99);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 21, 0);
	glScalef(10, 10, 10);
	glCallList(5);
	glPopMatrix();
	glTranslatef(0, 28.5, 30);
	glRotatef(180, 0, 1, 0);
	glCallList(99);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(30, 28.5, 28);
	glRotatef(191, 0, 1, 0);
	glCallList(99);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-31, 28.5, 29);
	glRotatef(170, 0, 1, 0);
	glCallList(99);
	glPopMatrix();
}

void mouse(int key, int stat, int x, int y)
{
	switch (key)
	{
		// case GLUT_LEFT_BUTTON:
		// 	if (stat)
		// 	{
		// 		t -= 0.05;
		// 	}
		// 	break;
	case GLUT_RIGHT_BUTTON:
		if (stat)
		{
			sprinting = false;
		}
		else
		{
			sprinting = true;
		}
		break;

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
		if (sprinting)
		{
			Ex = Ex + 5 * cos(th);
			Ez = Ez + 5 * sin(th);
		}
		else
		{
			Ex = Ex + cos(th);
			Ez = Ez + sin(th);
		}
		break;
	case GLUT_KEY_DOWN:
		if (sprinting)
		{
			Ex = Ex - 5 * cos(th);
			Ez = Ez - 5 * sin(th);
		}
		else
		{
			Ex = Ex - cos(th);
			Ez = Ez - sin(th);
		}
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

void testCollision()
{
	if (E < 0)
	{
		E = 0;
		velocity = 0;
	}

	if (E < (Ez + 144) * tan(-0.5) && E > ((Ez + 144) * tan(-0.5)) - 3)
	{
		E = (Ez + 144) * tan(-0.5);
		velocity = 0;
	}

	if (E < 38.5 && E > 35 && velocity < 0)
	{
		E = 38.5;
		velocity = 0;
	}
}

void doPhisics()
{
	velocity += acciliration;
	E += velocity;

	testCollision();
}

void initChairList()
{
	glPushMatrix();
	glNewList(8, GL_COMPILE);
	glColor3ub(90, 90, 90);
	GLUquadric *a = gluNewQuadric();
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
	GLUquadric *a = gluNewQuadric();

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
	GLUquadric *a = gluNewQuadric();
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

	//////////////////////////////////////////////////godfather

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
	glScalef(1.1, 1.2, 1.1);
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
	gluCylinder(a, 0.19, 0.19, 1.5, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5, 2.7, -6.6);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(1.3, 2.7, 3.8);
	gluCylinder(a, 0.19, 0.19, 1.5, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.5, 2.7, -6.6);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(1.3, 2.7, 3.8);
	gluCylinder(a, 0.19, 0.19, 1.5, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.5, 2.7, 6.6);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(1.3, 2.7, 3.8);
	gluCylinder(a, 0.19, 0.19, 1.5, 30, 30);
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
	gluSphere(a, 2, 30, 30);
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
	gluSphere(a, 1.1, 30, 30);
	glPopMatrix();
	///////////////////

	glPushMatrix();
	glTranslated(1.5, 0.6, 0.69);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(0.8, 1, 2.3);
	gluCylinder(a, 0.19, 0.19, 1.5, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.5, 0.6, -0.69);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(0.8, 1, 2.3);
	gluCylinder(a, 0.19, 0.19, 1.5, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.9, 0.6, -0.69);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(0.8, 1, 2.3);
	gluCylinder(a, 0.19, 0.19, 1.5, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.9, 0.6, 0.69);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1, 0, 0);
	glScalef(0.8, 1, 2.3);
	gluCylinder(a, 0.19, 0.19, 1.5, 30, 30);
	glPopMatrix();
	glPopMatrix();
	glEndList();

	///////////godfather
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
	///////////////////////////////////////////////////////////////////////////
	///////////wall godfather
	glNewList(24, GL_COMPILE);

	// godfather
	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(416, 0, -71);
	glBegin(GL_QUADS);
	glVertex3f(-25.0f, 0.0f, -120.0f);
	glVertex3f(-25.0f, 38.5f, -120.0f);
	glVertex3f(120.0f, 38.5f, -120.0f);
	glVertex3f(120.0f, 0.0f, -120.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(416, 0, 135);
	glBegin(GL_QUADS);
	glVertex3f(-25.0f, 0.0f, -120.0f);
	glVertex3f(-25.0f, 38.5f, -120.0f);
	glVertex3f(120.0f, 38.5f, -120.0f);
	glVertex3f(120.0f, 0.0f, -120.0f);
	glEnd();
	glPopMatrix();

	//////  godfather door

	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(361, 0, -123);
	glBegin(GL_QUADS);
	glVertex3f(30.0f, 0.0f, -30.0f);
	glVertex3f(30.0f, 38.5f, -30.0f);
	glVertex3f(30.0f, 38.5f, 30.0f);
	glVertex3f(30.0f, 0.0f, 30.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(348, 0, -28);
	glBegin(GL_QUADS);
	glVertex3f(43.0f, 0.0f, -43.0f);
	glVertex3f(43.0f, 38.5f, -43.0f);
	glVertex3f(43.0f, 38.5f, 43.0f);
	glVertex3f(43.0f, 0.0f, 43.0f);
	glEnd();
	glPopMatrix();

	//////////
	glPushMatrix();
	glColor3ub(245, 241, 190);
	glTranslatef(431, 0, -90);
	glBegin(GL_QUADS);
	glVertex3f(105.0f, 0.0f, -105.0f);
	glVertex3f(105.0f, 38.5f, -105.0f);
	glVertex3f(105.0f, 38.5f, 105.0f);
	glVertex3f(105.0f, 0.0f, 105.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(371, 0, -28);
	glBegin(GL_QUADS);
	glVertex3f(43.0f, 0.0f, -43.0f);
	glVertex3f(43.0f, 38.5f, -43.0f);
	glVertex3f(43.0f, 38.5f, 43.0f);
	glVertex3f(43.0f, 0.0f, 43.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(404, 0, -60.9);
	glBegin(GL_QUADS);
	glVertex3f(-12.9f, 0.0f, -10.0f);
	glVertex3f(-12.9f, 38.5f, -10.0f);
	glVertex3f(10.0f, 38.5f, -10.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();

	////////door
	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(389.1, 32.5, -82.1);
	glScaled(1, 0.16, 5.59);
	glBegin(GL_QUADS);
	glVertex3f(2.0f, 0.0f, -2.0f);
	glVertex3f(2.0f, 38.5f, -2.0f);
	glVertex3f(2.0f, 38.5f, 2.0f);
	glVertex3f(2.0f, 0.0f, 2.0f);
	glEnd();
	glPopMatrix();

	glEndList();

	///////خزنة

	glNewList(26, GL_COMPILE);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glTranslated(36, 2.39, -5);
	glColor3f(0.1, 0.2, 0.3);
	glBegin(GL_QUADS);
	glVertex3d(0.5, 5, 15);
	glVertex3d(-0.5, 5, 15);
	glVertex3d(-0.5, 5, -15);
	glVertex3d(0.5, 5, -15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-7, 11, 42);
	glColor3f(0.1, 0.2, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-7, 17, 41);
	glScalef(0.5, 0.3, 5);
	glColor3f(0.1, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-7, 18, 41);
	glScalef(0.5, 0.3, 5);
	glColor3f(0.1, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-7, 16, 41);
	glScalef(0.5, 0.3, 5);
	glColor3f(0.1, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	//
	glPushMatrix();
	glTranslated(-7, -5, 42);
	glColor3f(0.1, 0.2, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-7, 2, 41);
	glScalef(0.5, 0.3, 5);
	glColor3f(0.1, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-7, 1, 41);
	glScalef(0.5, 0.3, 5);
	glColor3f(0.1, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-7, 0, 41);
	glScalef(0.5, 0.3, 5);
	glColor3f(0.1, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glEndList();

	///////خزنة

	glNewList(27, GL_COMPILE);
	// خزنة
	glPushMatrix();
	glScalef(1, 0.9, 1);
	glTranslatef(382.5, 13, 0);
	glPushMatrix();
	glTranslated(0, 4.6, 0);
	glColor3f(0.1, 0.2, 0.3);
	glScalef(2, 5, 13);
	glutSolidCube(7);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glTranslated(0, 2.2, -5);
	// glScalef(1, 1, 1.8);
	glColor3f(0.4, 0.3, 0.5);
	glBegin(GL_QUADS);
	glVertex3d(42, 5, 15);
	glVertex3d(-42, 5, 15);
	glVertex3d(-42, 5, -15);
	glVertex3d(42, 5, -15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glTranslated(0, 2.32, -5);

	glColor3f(0.1, 0.2, 0.3);
	glBegin(GL_QUADS);
	glVertex3d(42, 5, 1.5);
	glVertex3d(-42, 5, 1.5);
	glVertex3d(-42, 5, -1.5);
	glVertex3d(42, 5, -1.5);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, -88);
	for (int i = 0; i < 9; i++)
	{
		glTranslated(0, 0, 9.5);
		glCallList(26);
	}
	glPopMatrix();
	glPopMatrix();
	glEndList();

	glNewList(28, GL_COMPILE);
	glPushMatrix();
	glScaled(5.5, 5.5, 5.5);
	glTranslated(-46.3, 7, -16.4);
	for (int i = 0; i < 1; i++)
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

	glEndList();
}

void InitGL(void)
{
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	// glClearColor(1.0f, 1.0f, 1.0f, 0.5f);				// Black Background
	// glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	GLfloat am[] = {0, 0, 0, 0.5};
	glLightfv(GL_LIGHT0, GL_AMBIENT, am);
	GLfloat di[] = {1, 1, 1, 0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, di);
	GLfloat sp[] = {1, 1, 1, 0};
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

	GLfloat position[] = {0, 1000, 0, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	gluLookAt(Ex, E + 18, Ez, Ex + cos(th), E + 18, Ez + sin(th), 0, 1, 0);
	GLUquadricObj *a = gluNewQuadric();

	/////////////////////////////////////////////////////////////////

	// fist staircase
	glColor3ub(245, 241, 185);
	glPushMatrix();
	glTranslatef(367, 0, -145);
	glRotatef(90, 0, 1, 0);
	glScalef(3.85, 3.85, 6);
	glCallList(36);
	glPopMatrix();

	// the godfather
	glPushMatrix();
	glTranslatef(445.7, 4, -50);
	glScalef(2, 2, 2);
	glRotatef(-90, 0, 1, 0);
	glCallList(20);
	glPopMatrix();
	// wall godfather
	glPushMatrix();
	glCallList(24);
	glPopMatrix();
	// window
	glPushMatrix();
	glTranslatef(535.8, 18, -180);
	glScalef(5.9, 5.9, 5.9);
	for (int i = 0; i < 8; i++)
	{
		glCallList(5);
		glTranslatef(0, 0, 2);
	}
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(190.8, 18, 410);
	glScalef(5.9, 5.9, 5.9);
	for (int i = 0; i < 10; i++)
	{
		glCallList(5);
		glTranslatef(0, 0, 2);
	}
	glPopMatrix();
	// door   godfather
	glPushMatrix();
	glTranslatef(391, 16, -70);
	glScalef(3, 4.2, 5.9);
	glRotatef(-270, 0, 1, 0);
	drewDoor();
	glPopMatrix();

	// ارض ط1 كامله
	glPushMatrix();
	glScaled(50, 5.5, 15);
	glTranslated(-1, 0, 0.37);
	glPushMatrix();
	glScalef(0.65, 0, 1);
	glTranslated(5.4, 0, 0);
	glColor3ub(130, 130, 130);
	glutSolidCube(40);
	glPopMatrix();

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

	gluLookAt(Ex, E + 18, Ez, Ex + cos(th), E + 18, Ez + sin(th), 0, 1, 0);
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
	//////////////////////////////////////////////////////////////////////
	/*
	glPushMatrix();
	glScalef(3, 0, 4);
	glTranslated(2, -1, 0);
	glColor3ub(130, 10, 130);
	glutSolidCube(2);
	glPopMatrix();
	*/

	glPopMatrix();
	/////////////////////////////////////////////////////////

	///////////////////////////////////
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
	gluLookAt(Ex, E + 18, Ez, Ex + cos(th), E + 18, Ez + sin(th), 0, 1, 0);

	// المدخل

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

	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(333, 0, -135);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 38.5f, -10.0f);
	glVertex3f(10.0f, 38.5f, -10.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();

	////door
	glPushMatrix();
	glColor4f(0, 0, 0.65, 0.25);
	glTranslatef(301, 0, -121);
	glBegin(GL_QUADS);
	glVertex3f(-15.0f, 0.0f, -23.5f);
	glVertex3f(-15.0f, 38.5f, -23.5f);
	glVertex3f(23.5f, 38.5f, -23.5f);
	glVertex3f(23.5f, 0.0f, -23.5f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 141, 0);
	glTranslatef(308, 0, -144);
	glScaled(0.3, 76.5, 0.7);
	glutSolidCube(1);
	glPopMatrix();

	////////////////////////////////////////////////////////////////////////
	/*
	glPushMatrix();
	glColor3ub(245, 241, 185);
	glTranslatef(333, 0, -135);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 38.5f, -10.0f);
	glVertex3f(10.0f, 38.5f, -10.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
	*/

	// wall left
	glPushMatrix();
	glColor3ub(245, 241, 185);

	glTranslatef(290, 0, 204.8);
	glBegin(GL_QUADS);
	glVertex3f(-50.0f, 0.0f, -50.0f);
	glVertex3f(-50.0f, 38.5f, -50.0f);
	glVertex3f(50.0f, 38.5f, -50.0f);
	glVertex3f(50.0f, 0.0f, -50.0f);
	glEnd();
	glPopMatrix();
	// class 1
	glPushMatrix();
	glTranslatef(394.6, 0, 210);
	glRotatef(180, 0, 1, 0);
	glScalef(5.5, 5.5, 5.5);
	glCallList(2);
	glCallList(7);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(504.6, 0, 210);
	glRotatef(180, 0, 1, 0);
	glScalef(5.5, 5.5, 5.5);
	glCallList(2);
	glCallList(7);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(301, 13.5, 155);
	glScalef(4.4, 3.5, 4.5);
	for (int i = 0; i < 2; i++)
	{

		glTranslated(25, 0, 0);
		drewDoor();
	}

	glPopMatrix();

	// wall
	glPushMatrix();
	glColor3ub(245, 241, 190);
	glTranslatef(454.6, 0, 90);
	glBegin(GL_QUADS);
	glVertex3f(105.0f, 0.0f, -105.0f);
	glVertex3f(105.0f, 38.5f, -105.0f);
	glVertex3f(105.0f, 38.5f, 105.0f);
	glVertex3f(105.0f, 0.0f, 105.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 241, 190);
	glTranslatef(368, 0, 38);
	glBegin(GL_QUADS);
	glVertex3f(23.0f, 0.0f, -23.0f);
	glVertex3f(23.0f, 38.5f, -23.0f);
	glVertex3f(23.0f, 38.5f, 23.0f);
	glVertex3f(23.0f, 0.0f, 23.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 241, 190);
	glTranslatef(435, 0, 201);
	glBegin(GL_QUADS);
	glVertex3f(-45.0f, 0.0f, -140.0f);
	glVertex3f(-45.0f, 38.5f, -140.0f);
	glVertex3f(140.0f, 38.5f, -140.0f);
	glVertex3f(140.0f, 0.0f, -140.0f);
	glEnd();
	glPopMatrix();

	///////خزنة
	glPushMatrix();
	glCallList(27);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-451, 0, 450);
	glCallList(27);
	glPopMatrix();
	////////////////////////////////////////////////////////////
	/////	ffff2

	glPushMatrix();
	glTranslatef(295, 38.49, -74.6);
	glScalef(10, 5.5, 10);
	glColor3ub(245, 241, 190);
	glBegin(GL_QUADS);
	glVertex3f(-5.7f, 0.0f, -7.0f);
	glVertex3f(-5.7f, 7.0f, -7.0f);
	glVertex3f(7.0f, 7.0f, -7.0f);
	glVertex3f(7.0f, 0.0f, -7.0f);
	glEnd();
	glPopMatrix();

	////wind  f2
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(144, 55, 260);
	glScalef(5.9, 5.9, 5.9);
	for (int i = 0; i < 8; i++)
	{
		glCallList(5);
		glTranslatef(0, 0, 2);
	}
	glPopMatrix();
	////////////////////////////////////////////

	glPushMatrix();
	glTranslatef(295, 38.49, -74.6);
	glScalef(10, 5.5, 10);
	glPushMatrix();
	glColor3ub(245, 241, 190);
	glBegin(GL_QUADS);
	glVertex3f(-5.7f, 0.0f, -7.0f);
	glVertex3f(-5.7f, 7.0f, -7.0f);
	glVertex3f(7.0f, 7.0f, -7.0f);
	glVertex3f(7.0f, 0.0f, -7.0f);
	glEnd();
	glPopMatrix();
	/*
	glPushMatrix();
	glColor3ub(245, 241, 5);
	glBegin(GL_QUADS);
	glVertex3f(-2.0f, 0.0f, 8.0f);
	glVertex3f(-2.0f, 7.0f, 8.0f);
	glVertex3f(8.0f, 7.0f, 8.0f);
	glVertex3f(8.0f, 0.0f, 8.0f);
	glEnd();
	glPopMatrix();*/
	glPopMatrix();

	//////////////////////////
	glPushMatrix();
	glColor3ub(245, 241, 190);
	glTranslatef(368, 38, 38);
	glBegin(GL_QUADS);
	glVertex3f(23.0f, 0.0f, -23.0f);
	glVertex3f(23.0f, 38.5f, -23.0f);
	glVertex3f(23.0f, 38.5f, 23.0f);
	glVertex3f(23.0f, 0.0f, 23.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(590.2, 0, -48);
	glCallList(28);
	glPopMatrix();
	/////////////////
	glPushMatrix();
	glTranslatef(5, 0, -10);
	glRotated(180, 0, 1, 0);
	glCallList(28);
	glPopMatrix();

	if (phisics)
	{
		doPhisics();
	}

	printFPS();

	// غرف الادارة طابق 1
	/// / 2غرفة الدكاترة

	glPushMatrix();
	glTranslated(-400, 2, 110);
	glRotated(180, 0, 1, 0);
	glScaled(0.6, 0.6, 0.6);
	glPushMatrix();

	glTranslated(37, -3, 0);
	glScalef(1, 0, 1);
	glColor3ub(130, 130, 130);
	glutSolidCube(200);

	glPopMatrix();

	glPushMatrix();
	glTranslated(137, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor3ub(245, 241, 185);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37, 19.5, -100);
	glRotated(90, 0, 1, 0);
	glScalef(0, 5, 22.2);
	glColor3ub(125, 156, 159);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-63, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor3ub(245, 241, 185);
	glutSolidCube(13.33);
	glPopMatrix();

	/// سقف
	glPushMatrix();
	glTranslated(37, 41, 0);
	glScalef(1, 0, 1);
	glColor3ub(245, 241, 185);
	glutSolidCube(200);
	glPopMatrix();

	glTranslatef(0, 12, -50);
	glRotatef(-90, 1, 0, 0);
	//	GLUquadricObj* a = gluNewQuadric();
	glColor3f(0.01, 0, 0);

	///////مكتب

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();

	///////////لابتوب

	glPushMatrix();

	glTranslated(-25, -30, -16);

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 30, 20);
	glScaled(2, 2, 0.2);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 26, 24);
	glScaled(2, 0.2, 2);
	glutSolidCube(4);

	glPopMatrix();
	glPopMatrix();

	/// مكتب على اليمين

	glPushMatrix();

	glTranslated(55, 10, 0);
	glRotated(-90, 0, 0, 1);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();

	///////////لابتوب

	glPushMatrix();

	glTranslated(-25, -30, -16);

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 30, 20);
	glScaled(2, 2, 0.2);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 26, 24);
	glScaled(2, 0.2, 2);
	glutSolidCube(4);

	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	/// //مكتب على اليسار

	glPushMatrix();

	glTranslated(-15, -50, 0);
	glRotated(90, 0, 0, 1);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	/// /مكتب الطابعة

	glPushMatrix();

	glTranslated(-15, 30, 0);
	// glScaled(2, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	// طابعة

	glPushMatrix();
	glTranslated(-25, 30, 10.5);
	glScaled(2.5, 2.5, 2.5);
	glPushMatrix();

	/*glTranslated(0, -3, 0);
	glScalef(1, 0, 1);*/
	glColor3ub(59, 59, 59);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1.5, 0, 3);
	glScalef(0.5, 1.5, 0.5);
	glColor3ub(59, 59, 59);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 0, 3.5);
	glScaled(5, -3, 0);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);

	glPopMatrix();

	/*تفاصيل الطابعة*/

	glPushMatrix();
	glColor3f(0.06, 0.7, 0.3);
	glTranslated(0, -2.5, -2);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.06, 0.7, 0.3);
	glTranslated(0, -2.5, -1);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(-1.5, -2.5, 1.5);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.8);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(1, -2.5, 1.5);
	glScaled(5, 0.1, 0.4);
	glutSolidCube(0.6);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.5, -2);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.6, -2);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.6, -1);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glColor3f(546, 34, 45);
	glTranslated(-6, 25, 6);
	glScaled(1, 1, 0.3);
	glutSolidCube(7);
	glPopMatrix();

	///////الباب
	glPushMatrix();

	glRotatef(90, 1, 0, 0);
	glTranslated(21.9, 7, 150);
	glScaled(7, 5.5, 6);
	drewDoor();
	glPopMatrix();

	/// حيط الباب
	glPushMatrix();

	glTranslated(93, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 10);
	glColor3ub(245, 241, 185);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();

	glTranslated(-21, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 9.5);
	glColor3ub(245, 241, 185);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-50, 40, 10);
	glScaled(15, 15, 15);
	glRotated(90, 45, 1, 0);
	for (int i = 0; i < 5; i++)
	{
		glTranslated(0, 0, 1.9);
		glCallList(5);
	}
	glPopMatrix();
	glPopMatrix();

	/// / 1غرفة الدكاترة

	glPushMatrix();
	glTranslated(-270, 2, 110);
	glRotated(180, 0, 1, 0);
	glScaled(0.6, 0.6, 0.6);
	glPushMatrix();

	glTranslated(37, -3, 0);
	glScalef(1, 0, 1);
	glColor3ub(130, 130, 130);
	glutSolidCube(200);

	glPopMatrix();

	glPushMatrix();
	glTranslated(137, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor3ub(245, 241, 185);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37, 19.5, -100);
	glRotated(90, 0, 1, 0);
	glScalef(0, 5, 22.2);
	glColor3ub(125, 156, 159);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-63, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor3ub(245, 241, 185);
	glutSolidCube(13.33);
	glPopMatrix();

	/// سقف
	glPushMatrix();
	glTranslated(37, 41, 0);
	glScalef(1, 0, 1);
	glColor3ub(245, 241, 185);
	glutSolidCube(200);
	glPopMatrix();

	glTranslatef(0, 12, -50);
	glRotatef(-90, 1, 0, 0);
	//	GLUquadricObj* a = gluNewQuadric();
	glColor3f(0.01, 0, 0);

	///////مكتب

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();

	///////////لابتوب

	glPushMatrix();

	glTranslated(-25, -30, -16);

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 30, 20);
	glScaled(2, 2, 0.2);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 26, 24);
	glScaled(2, 0.2, 2);
	glutSolidCube(4);

	glPopMatrix();
	glPopMatrix();

	/// مكتب على اليمين

	glPushMatrix();

	glTranslated(55, 10, 0);
	glRotated(-90, 0, 0, 1);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();

	///////////لابتوب

	glPushMatrix();

	glTranslated(-25, -30, -16);

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 30, 20);
	glScaled(2, 2, 0.2);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 26, 24);
	glScaled(2, 0.2, 2);
	glutSolidCube(4);

	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	/// //مكتب على اليسار

	glPushMatrix();

	glTranslated(-15, -50, 0);
	glRotated(90, 0, 0, 1);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	/// /مكتب الطابعة

	glPushMatrix();

	glTranslated(-15, 30, 0);
	// glScaled(2, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	// طابعة

	glPushMatrix();
	glTranslated(-25, 30, 10.5);
	glScaled(2.5, 2.5, 2.5);
	glPushMatrix();

	/*glTranslated(0, -3, 0);
	glScalef(1, 0, 1);*/
	glColor3ub(59, 59, 59);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1.5, 0, 3);
	glScalef(0.5, 1.5, 0.5);
	glColor3ub(59, 59, 59);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 0, 3.5);
	glScaled(5, -3, 0);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);

	glPopMatrix();

	/*تفاصيل الطابعة*/

	glPushMatrix();
	glColor3f(0.06, 0.7, 0.3);
	glTranslated(0, -2.5, -2);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.06, 0.7, 0.3);
	glTranslated(0, -2.5, -1);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(-1.5, -2.5, 1.5);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.8);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(1, -2.5, 1.5);
	glScaled(5, 0.1, 0.4);
	glutSolidCube(0.6);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.5, -2);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.6, -2);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.6, -1);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glColor3f(546, 34, 45);
	glTranslated(-6, 25, 6);
	glScaled(1, 1, 0.3);
	glutSolidCube(7);
	glPopMatrix();

	///////الباب
	glPushMatrix();

	glRotatef(90, 1, 0, 0);
	glTranslated(21.9, 7, 150);
	glScaled(7, 5.5, 6);
	drewDoor();
	glPopMatrix();

	/// حيط الباب
	glPushMatrix();

	glTranslated(93, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 10);
	glColor3ub(245, 241, 185);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();

	glTranslated(-21, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 9.5);
	glColor3ub(245, 241, 185);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-50, 40, 10);
	glScaled(15, 15, 15);
	glRotated(90, 45, 1, 0);
	for (int i = 0; i < 5; i++)
	{
		glTranslated(0, 0, 1.9);
		glCallList(5);
	}
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();

	glTranslated(-480, 1, -90);
	glScaled(5.5, 5.5, 5.5);
	for (int i = 0; i < 3; i++)
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

	// قاعات الطابق الثاني ادارة

	// غرف الادارة طابق 1
	/// / 2غرفة الدكاترة

	glPushMatrix();
	glTranslated(-400, 38.5, 90);
	glPushMatrix();
	glTranslated(-400, 2, 110);
	glRotated(180, 0, 1, 0);
	glScaled(0.6, 0.6, 0.6);
	glPushMatrix();

	glTranslated(37, -3, 0);
	glScalef(1, 0, 1);
	glColor3ub(130, 130, 130);
	glutSolidCube(200);

	glPopMatrix();

	glPushMatrix();
	glTranslated(137, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor3ub(245, 241, 185);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37, 19.5, -100);
	glRotated(90, 0, 1, 0);
	glScalef(0, 5, 22.2);
	glColor3ub(125, 156, 159);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-63, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor3ub(245, 241, 185);
	glutSolidCube(13.33);
	glPopMatrix();

	/// سقف
	glPushMatrix();
	glTranslated(37, 41, 0);
	glScalef(1, 0, 1);
	glColor3ub(245, 241, 185);
	glutSolidCube(200);
	glPopMatrix();

	glTranslatef(0, 12, -50);
	glRotatef(-90, 1, 0, 0);
	//	GLUquadricObj* a = gluNewQuadric();
	glColor3f(0.01, 0, 0);

	///////مكتب

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();

	///////////لابتوب

	glPushMatrix();

	glTranslated(-25, -30, -16);

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 30, 20);
	glScaled(2, 2, 0.2);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 26, 24);
	glScaled(2, 0.2, 2);
	glutSolidCube(4);

	glPopMatrix();
	glPopMatrix();

	/// مكتب على اليمين

	glPushMatrix();

	glTranslated(55, 10, 0);
	glRotated(-90, 0, 0, 1);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();

	///////////لابتوب

	glPushMatrix();

	glTranslated(-25, -30, -16);

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 30, 20);
	glScaled(2, 2, 0.2);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 26, 24);
	glScaled(2, 0.2, 2);
	glutSolidCube(4);

	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	/// //مكتب على اليسار

	glPushMatrix();

	glTranslated(-15, -50, 0);
	glRotated(90, 0, 0, 1);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	/// /مكتب الطابعة

	glPushMatrix();

	glTranslated(-15, 30, 0);
	// glScaled(2, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	// طابعة

	glPushMatrix();
	glTranslated(-25, 30, 10.5);
	glScaled(2.5, 2.5, 2.5);
	glPushMatrix();

	/*glTranslated(0, -3, 0);
	glScalef(1, 0, 1);*/
	glColor3ub(59, 59, 59);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1.5, 0, 3);
	glScalef(0.5, 1.5, 0.5);
	glColor3ub(59, 59, 59);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 0, 3.5);
	glScaled(5, -3, 0);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);

	glPopMatrix();

	/*تفاصيل الطابعة*/

	glPushMatrix();
	glColor3f(0.06, 0.7, 0.3);
	glTranslated(0, -2.5, -2);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.06, 0.7, 0.3);
	glTranslated(0, -2.5, -1);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(-1.5, -2.5, 1.5);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.8);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(1, -2.5, 1.5);
	glScaled(5, 0.1, 0.4);
	glutSolidCube(0.6);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.5, -2);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.6, -2);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.6, -1);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glColor3f(546, 34, 45);
	glTranslated(-6, 25, 6);
	glScaled(1, 1, 0.3);
	glutSolidCube(7);
	glPopMatrix();

	///////الباب
	glPushMatrix();

	glRotatef(90, 1, 0, 0);
	glTranslated(21.9, 7, 150);
	glScaled(7, 5.5, 6);
	drewDoor();
	glPopMatrix();

	/// حيط الباب
	glPushMatrix();

	glTranslated(93, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 10);
	glColor3ub(245, 241, 185);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();

	glTranslated(-21, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 9.5);
	glColor3ub(245, 241, 185);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-50, 40, 10);
	glScaled(15, 15, 15);
	glRotated(90, 45, 1, 0);
	for (int i = 0; i < 5; i++)
	{
		glTranslated(0, 0, 1.9);
		glCallList(5);
	}
	glPopMatrix();
	glPopMatrix();

	/// / 1غرفة الدكاترة

	glPushMatrix();
	glTranslated(-270, 2, 110);
	glRotated(180, 0, 1, 0);
	glScaled(0.6, 0.6, 0.6);
	glPushMatrix();

	glTranslated(37, -3, 0);
	glScalef(1, 0, 1);
	glColor3ub(130, 130, 130);
	glutSolidCube(200);

	glPopMatrix();

	glPushMatrix();
	glTranslated(137, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor3ub(245, 241, 185);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37, 19.5, -100);
	glRotated(90, 0, 1, 0);
	glScalef(0, 5, 22.2);
	glColor3ub(125, 156, 159);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-63, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor3ub(245, 241, 185);
	glutSolidCube(13.33);
	glPopMatrix();

	/// سقف
	glPushMatrix();
	glTranslated(37, 41, 0);
	glScalef(1, 0, 1);
	glColor3ub(245, 241, 185);
	glutSolidCube(200);
	glPopMatrix();

	glTranslatef(0, 12, -50);
	glRotatef(-90, 1, 0, 0);
	//	GLUquadricObj* a = gluNewQuadric();
	glColor3f(0.01, 0, 0);

	///////مكتب

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();

	///////////لابتوب

	glPushMatrix();

	glTranslated(-25, -30, -16);

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 30, 20);
	glScaled(2, 2, 0.2);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 26, 24);
	glScaled(2, 0.2, 2);
	glutSolidCube(4);

	glPopMatrix();
	glPopMatrix();

	/// مكتب على اليمين

	glPushMatrix();

	glTranslated(55, 10, 0);
	glRotated(-90, 0, 0, 1);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();

	///////////لابتوب

	glPushMatrix();

	glTranslated(-25, -30, -16);

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 30, 20);
	glScaled(2, 2, 0.2);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 26, 24);
	glScaled(2, 0.2, 2);
	glutSolidCube(4);

	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	/// //مكتب على اليسار

	glPushMatrix();

	glTranslated(-15, -50, 0);
	glRotated(90, 0, 0, 1);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	/// /مكتب الطابعة

	glPushMatrix();

	glTranslated(-15, 30, 0);
	// glScaled(2, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	// طابعة

	glPushMatrix();
	glTranslated(-25, 30, 10.5);
	glScaled(2.5, 2.5, 2.5);
	glPushMatrix();

	/*glTranslated(0, -3, 0);
	glScalef(1, 0, 1);*/
	glColor3ub(59, 59, 59);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1.5, 0, 3);
	glScalef(0.5, 1.5, 0.5);
	glColor3ub(59, 59, 59);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 0, 3.5);
	glScaled(5, -3, 0);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);

	glPopMatrix();

	/*تفاصيل الطابعة*/

	glPushMatrix();
	glColor3f(0.06, 0.7, 0.3);
	glTranslated(0, -2.5, -2);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.06, 0.7, 0.3);
	glTranslated(0, -2.5, -1);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(-1.5, -2.5, 1.5);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.8);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(1, -2.5, 1.5);
	glScaled(5, 0.1, 0.4);
	glutSolidCube(0.6);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.5, -2);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.6, -2);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.6, -1);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glColor3f(546, 34, 45);
	glTranslated(-6, 25, 6);
	glScaled(1, 1, 0.3);
	glutSolidCube(7);
	glPopMatrix();

	///////الباب
	glPushMatrix();

	glRotatef(90, 1, 0, 0);
	glTranslated(21.9, 7, 150);
	glScaled(7, 5.5, 6);
	drewDoor();
	glPopMatrix();

	/// حيط الباب
	glPushMatrix();

	glTranslated(93, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 10);
	glColor3ub(245, 241, 185);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();

	glTranslated(-21, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 9.5);
	glColor3ub(245, 241, 185);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-50, 40, 10);
	glScaled(15, 15, 15);
	glRotated(90, 45, 1, 0);
	for (int i = 0; i < 5; i++)
	{
		glTranslated(0, 0, 1.9);
		glCallList(5);
	}
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();

	glTranslated(-480, 1, -90);
	glScaled(5.5, 5.5, 5.5);
	for (int i = 0; i < 3; i++)
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

	// غرفة العميد

	glPushMatrix();
	glTranslated(-540, 2, 110);
	glRotated(180, 0, 1, 0);
	glScaled(0.6, 0.6, 0.6);
	glPushMatrix();

	glTranslated(37, -3, 0);
	glScalef(0.7, 0, 1);
	glColor3ub(130, 130, 130);
	glutSolidCube(200);

	glPopMatrix();

	glPushMatrix();
	glTranslated(107, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor3ub(245, 241, 185);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37.2, 19.4, -100);
	glRotated(90, 0, 1, 0);
	glScalef(0, 5, 15.6);
	glColor3ub(245, 241, 185);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-33, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor3ub(245, 241, 185);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37, 41, 0);
	glScalef(0.7, 0, 1);
	glColor3ub(245, 241, 185);
	glutSolidCube(200);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 12, -50);
	glRotatef(-90, 1, 0, 0);
	// GLUquadricObj a = gluNewQuadric();
	glColor3f(0.01, 0, 0);

	// مكتب

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(40, 7, 7);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3ub(40, 7, 7);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3ub(40, 7, 7);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//; كرسي الضيوف

	glPushMatrix();

	glTranslated(0, -37, 0);

	glPushMatrix();

	glTranslated(4, 15, -10);
	glScalef(2, 2, 1.2);
	glColor3ub(28, 18, 18);
	glutSolidCube(6);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1, 15, -2.5);
	glScalef(0.5, 2.5, 1.5);
	glColor3ub(28, 18, 18);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(4.6, 20, -6.3);
	glScalef(1.3, 0.5, 0.8);
	glColor3ub(78, 62, 62);
	gluCylinder(a, 4, 4, 3.5, 30, 30);

	glPopMatrix();

	glPushMatrix();

	glTranslated(4.6, 9, -6.3);
	glScalef(1.3, 0.5, 0.8);
	glColor3ub(78, 62, 62);
	gluCylinder(a, 4, 4, 3.5, 30, 30);

	glPopMatrix();

	glPopMatrix();

	// كرسي الضيوف التاني

	glPushMatrix();

	glTranslated(60, -37, 0);

	glPushMatrix();

	glTranslated(-4, 15, -10);
	glScalef(2, 2, 1.2);
	glColor3ub(28, 18, 18);
	glutSolidCube(6);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 15, -2.5);
	glScalef(0.5, 2.5, 1.5);
	glColor3ub(28, 18, 18);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-4.6, 20, -6.3);
	glScalef(1.3, 0.5, 0.8);
	glColor3ub(78, 62, 62);
	gluCylinder(a, 4, 4, 3.5, 30, 30);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-4.6, 9, -6.3);
	glScalef(1.3, 0.5, 0.8);
	glColor3ub(78, 62, 62);
	gluCylinder(a, 4, 4, 3.5, 30, 30);

	glPopMatrix();

	glPopMatrix();

	//	طاولة القهوة

	glPushMatrix();

	glTranslated(1, 5, 0);

	glPushMatrix();

	glTranslated(30, -30, -5);
	glScaled(1, 1, 0.2);
	gluSphere(a, 8, 10, 30);

	glPopMatrix();

	glPushMatrix();

	glTranslated(30, -30, -15);
	gluCylinder(a, 1, 1, 10, 30, 30);

	glPopMatrix();

	glPopMatrix();

	// غراض الطاولة

	//	ابريق
	glPushMatrix();

	glPushMatrix();
	glColor3f(0.32, 0.03, 0.05);
	glTranslated(31, -30, -2.7);
	glScaled(3, 3, 3);
	glRotated(90, 90, 30, 30);
	glutSolidTeapot(0.4);
	glPopMatrix();

	// فنجان1
	glPushMatrix();

	glColor3f(0.32, 0.03, 0.05);
	glTranslated(28, -30, -3.5);
	gluCylinder(a, 0.4, 0.4, 0.5, 30, 30);
	gluDisk(a, 0.02, 1, 30, 30);

	glPopMatrix();

	// فنجان2

	glPushMatrix();

	glColor3f(0.32, 0.03, 0.05);
	glTranslated(28, -28, -3.5);
	gluCylinder(a, 0.4, 0.4, 0.5, 30, 30);
	gluDisk(a, 0.02, 1, 30, 30);

	glPopMatrix();

	glPopMatrix();

	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

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
	gluCylinder(a, 3, 3, 12, 100, 100);
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
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();

	//	لابتوب

	glPushMatrix();

	glTranslated(-25, -30, -15);

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 30, 20);
	glScaled(2, 2, 0.2);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 26, 24);
	glScaled(2, 0.2, 2);
	glutSolidCube(4);

	glPopMatrix();
	glPopMatrix();

	// طاولة الاجتماعات
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslated(40, -15, 80);
	glScaled(0.6, 0.6, 0.6);
	drewMeetingTable();
	glPopMatrix();

	glPushMatrix();

	glRotatef(90, 1, 0, 0);
	glTranslated(-200, -219, 150);
	glScaled(6, 5.5, 6);
	drewDoor();
	glPopMatrix();

	// حيط الباب
	glPushMatrix();

	glTranslated(75, -148, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 7);
	glColor3ub(245, 241, 185);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();

	glTranslated(-5, -148, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 6.3);
	glColor3ub(245, 241, 185);
	glutSolidCube(9);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

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

int main(int argc, char **argv)
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
	glutMouseFunc(mouse);
	Timer(0);
	glutDisplayFunc(DrawGLScene);
	setupprojection();
	glutMainLoop();
	return 0;
}