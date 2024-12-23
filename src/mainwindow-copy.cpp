#include <GL/glut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include <iostream>
using namespace std;

double th = 0;
double Ex = 0;
double Ez = 0;
double E = 0;#include <GL/glut.h>
#include <math.h>
#include <SOIL/SOIL.h>
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
bool light = false;
bool lighting = false;
bool rotate = false;
bool OpDoorOpen = false;
double pos = 0.0;
GLuint skyboxTexture;
GLUquadricObj *a = gluNewQuadric();

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: /* Escape key */
		exit(0);
		break;
	case 'q':
		E++;
		break;
	case 'z':
		E--;
		break;
	case 'r':
		if (rotate)
			rotate = false;
		else
			rotate = true;
		break;
	case 'l':
		if (light)
			light = false;
		else
			light = true;
		break;
	case 'L':
		if (lighting)
			lighting = false;
		else
			lighting = true;
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
	case 'p':
		if (OpDoorOpen)
		{
			OpDoorOpen = false;
		}
		else
		{
			OpDoorOpen = true;
		}
		break;
	case 'd':
		if (sprinting)
		{
			Ex = Ex + 5 * sin(th);
			Ez = Ez + 5 * cos(th);
		}
		else
		{
			Ex = Ex + 2 * sin(th);
			Ez = Ez + 2 * cos(th);
		}
		break;
	case 'a':
		if (sprinting)
		{
			Ex = Ex - 5 * sin(th);
			Ez = Ez - 5 * cos(th);
		}
		else
		{
			Ex = Ex - 2 * sin(th);
			Ez = Ez - 2 * cos(th);
		}
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

void loadSkyboxTexture()
{
	const char *skyboxFileName = "/home/mohamed/Documents/vscode/c++/obada/texture/skybox_right.jpg";

	skyboxTexture = SOIL_load_OGL_texture(
		skyboxFileName,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

	if (!skyboxTexture)
	{
		printf("Skybox texture loading failed for %s: %s\n", skyboxFileName, SOIL_last_result());
	}
}

void drawSkybox()
{
	glEnable(GL_TEXTURE_2D);
	glColor4ub(255, 255, 255, 255);

	// Draw the skybox cube (size can be adjusted)
	glBegin(GL_QUADS);

	// Front face
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-200, -200, -200);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(200, -200, -200);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(200, 200, -200);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-200, 200, -200);

	// Back face
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(200, -200, 200);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-200, -200, 200);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-200, 200, 200);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(200, 200, 200);

	// Left face
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-200, -200, -200);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-200, -200, 200);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-200, 200, 200);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-200, 200, -200);

	// Right face
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(200, -200, -200);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(200, -200, 200);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(200, 200, 200);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(200, 200, -200);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	// Top face
	glColor4ub(103, 133, 197, 255);
	glVertex3f(-200, 200, -200);
	glVertex3f(200, 200, -200);
	glVertex3f(200, 200, 200);
	glVertex3f(-200, 200, 200);

	// Bottom face
	glColor4ub(22, 69, 17, 255);
	glVertex3f(-200, -200, 200);
	glVertex3f(200, -200, 200);
	glVertex3f(200, -200, -200);
	glVertex3f(-200, -200, -200);

	glEnd();
}

void initMeetingChair()
{
	glPushMatrix();
	glNewList(99, GL_COMPILE);
	GLUquadric *a = gluNewQuadric();
	glColor4ub(100, 100, 100, 255);
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
	gluCylinder(a, 3, 3, 12, 50, 50);
	glPopMatrix();

	glColor4ub(20, 20, 15, 255);
	// base
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(0.6, 3.7, 50, 50);
	glPopMatrix();

	// back
	glPushMatrix();
	glRotatef(-5, 1, 0, 0);
	glScalef(1, 1.3, 0.4);
	gluSphere(a, 7, 50, 50);
	glPopMatrix();

	glColor4ub(100, 100, 100, 255);
	// arms
	glPushMatrix();
	glTranslatef(5, -14, 4);
	glRotatef(-90, 1, -0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -14, 4);
	glRotatef(-90, 1, 0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 50, 50);
	glPopMatrix();

	glColor4ub(20, 20, 15, 255);
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 50, 50);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 50, 50);
	glPopMatrix();

	glEndList();
	glPopMatrix();
}

void initAmbulance() {
	glNewList(1, GL_COMPILE);
	glPushMatrix();
	glTranslated(0, 1.4, 0);
	glScaled(0.4, 0.4, 0.35);
	//body

glPushMatrix();

glScalef(16, 1, 8);
glColor3f(0, 0, 0);
glutSolidCube(2);
glPopMatrix();


glPushMatrix();
glScalef(1.5, 0.5, 2);
glTranslated(-6.666666, 6, 0);
glColor3f(0, 0, 0);
glutSolidCube(8);
glPopMatrix();


glPushMatrix();
glScaled(1.2, 1, 2.666666);
glTranslated(-6.33333, 6, 0);
glColor3f(0, 0, 0);
glutSolidCube(6);
glPopMatrix();


glPushMatrix();

glScaled(1.8, 1, 1.33);
glTranslated(4, 7, 0);
glColor3ub(0, 0, 0);
glutSolidCube(12);
glPopMatrix();

glBegin(GL_QUADS);
glColor3ub(255, 255, 255);
glVertex3d(15.01, 1, 7);
glVertex3d(15.01, 1, -7);
glVertex3d(15.01, 11.5, -7);
glVertex3d(15.01, 11.5, 7);
glEnd();

//Bottom Lights
glPushMatrix();
glScalef(0.8, 1, 2);
glTranslated(-20, 0, 2.8);
glColor3ub(255, 145, 0);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glScalef(0.8, 1, 2);
glTranslated(-20, 0, -2.8);
glColor3ub(255, 145, 0);
glutSolidCube(1);
glPopMatrix();

//Bottom Lights
glPushMatrix();
glScaled(0.8, 1, 2);
glTranslated(20, 0, -2.8);
glColor3ub(255, 0, 0);
glutSolidCube(1);
glPopMatrix();


glPushMatrix();
glScaled(0.8, 1, 2);
glTranslated(20, 0, 2.8);
glColor3ub(255, 0, 0);
glutSolidCube(1);
glPopMatrix();


//side windows

glPushMatrix();
glScaled(1.1, 0.6, 3.202);
glTranslated(-6.9, 11, 0);
glColor3ub(184, 244, 255);
glutSolidCube(5);
glPopMatrix();

//Front window
glPushMatrix();
glScaled(1.2, 0.6, 2.6);
glTranslated(-7, 11, 0);
glColor3ub(184, 244, 255);
glutSolidCube(5);
glPopMatrix();

//Top Lights
glPushMatrix();
glScaled(0.4, 0.8, 2);
glTranslated(-40, 3.75, 2.8);
glColor3ub(255, 238, 173);
glutSolidCube(2);
glPopMatrix();


glPushMatrix();
glScaled(0.4, 0.8, 2);
glTranslated(-40, 3.75, -2.8);
glColor3ub(255, 238, 173);
glutSolidCube(2);
glPopMatrix();


//right front wheel
glTranslated(12, -1, 08.01);
glColor3ub(0, 0, 0);
gluPartialDisk(a, 2.5, 3., 30, 30, 270, 180);

glColor3d(0.1, 0.1, 0.1);
glutSolidTorus(0.8, 1.8, 30, 30);

glColor3ub(180, 180, 180);
gluDisk(a, 0, 2, 30, 30);

//left front wheel
glTranslated(-22, 0, 0);
glColor3ub(0, 0, 0);
gluPartialDisk(a, 2.5, 3., 30, 30, 270, 180);


glColor3f(0.1, 0.1, 0.1);
glutSolidTorus(0.8, 1.8, 30, 30);

glColor3ub(180, 180, 180);
gluDisk(a, 0, 2, 30, 30);

glTranslated(10, 1, -8.01);


//left back wheel
glTranslated(12, -1, -8.01);
glColor3ub(0, 0, 0);
gluPartialDisk(a, 2.5, 3., 30, 30, 270, 180);

glColor3f(0.1, 0.1, 0.1);
glutSolidTorus(0.8, 1.8, 30, 30);

glColor3ub(180, 180, 180);
gluDisk(a, 0, 2, 30, 30);

//right back wheel
glTranslated(-22, 0, 0);
glColor3ub(0, 0, 0);
gluPartialDisk(a, 2.5, 3., 30, 30, 270, 180);

glColor3f(0.1, 0.1, 0.1);
glutSolidTorus(0.8, 1.8, 30, 30);

glColor3ub(180, 180, 180);
gluDisk(a, 0, 2, 30, 30);

glTranslated(10, 1, 8.01);

glPopMatrix();


glPopMatrix();
	glPopMatrix();
	glEndList();
}

void initBed()
{
	glNewList(34, GL_COMPILE);
	glPushMatrix();
	glPushMatrix();
	glTranslated(0, 0.035, 0);
	glPushMatrix();
	glTranslated(0, 1.2, 0);
	glPushMatrix();
	glColor4ub(50, 255, 255, 255);
	glScalef(1, 0.2, 2);
	glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(0, -0.2, 0);
	glScalef(1, 0.1, 2);
	glutSolidCube(2);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(-0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(-0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glColor4ub(30, 30, 30, 255);
	glTranslated(-0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(30, 30, 30, 255);
	glTranslated(0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(30, 30, 30, 255);
	glTranslated(-0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(30, 30, 30, 255);
	glTranslated(0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(0, 1.33, 2);
	glScalef(1, 0.4, 0.05);
	glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(220, 220, 220, 255);
	glTranslated(0, 1.5, 1.6);
	glRotated(-7, 1, 0, 0);
	glScalef(1, 0.2, 0.5);
	glutSolidCube(1.4);
	glPopMatrix();
	glPopMatrix();
	glEndList();
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
	std::cout << '\r' << 1000 / deltaTime << " " << Ex << " " << E << " " << Ez << std::flush;
}

void initTree() {
	GLUquadric* quad = gluNewQuadric();
	glNewList(24, GL_COMPILE);
	glPushMatrix();
	// Draw trunk
    glColor3f(0.5, 0.35, 0.05);  // Brown color for trunk
    glPushMatrix();
	glRotatef(-90, 1, 0, 0.0);
    gluCylinder(quad, 0.6, 0.6, 4, 20, 20);  // Adjust the radius and height as needed
    glPopMatrix();

    // Draw branches
    glColor3f(0.0, 0.5, 0.0);  // Green color for branches
    glPushMatrix();
    glTranslatef(0.0, 3, 0.0);  // Adjust the translation as needed
    glRotatef(90, -1, 0, 0.0);  // Adjust the rotation as needed
    gluCylinder(quad, 3,0, 4, 20, 20);  // Adjust the radius and height as needed
    glPopMatrix();
	
	glPopMatrix();
	glEndList();
}

void initDoor()
{
	glPushMatrix();
	GLUquadric *a = gluNewQuadric();

	// doors
	glPushMatrix();
	glNewList(6, GL_COMPILE);
	glPushMatrix();
	glColor4ub(175, 125, 51, 255);
	glTranslatef(1.75, 0, 0);
	glScaled(1, 2, 0.08);
	glutSolidCube(3.5);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(220, 186, 136, 255);
	glTranslated(3.2, 0, -0.5);
	gluCylinder(a, 0.17, 0.17, 1, 30, 30);
	gluDisk(a, 0, 0.17, 30, 30);
	glTranslated(0, 0, 1);
	gluDisk(a, 0, 0.17, 30, 30);
	glPopMatrix();
	glEndList();
	glPopMatrix();
}

void drawDoor()
{
	if (doorOpen)
	{
		if (r2 > -90)
		{
			r2 -= deltaTime / 30.0;
		}
	}
	else
	{
		if (r2 < 0)
		{
			r2 += deltaTime / 30.0;
		}
	}
	// glRotatef(90, 1, 0, 0);

	glPushMatrix();
	glRotatef(r2, 0, 1, 0);
	glCallList(6);
	glPopMatrix();
}

void initCounter()
{
	////counter
	glNewList(21, GL_COMPILE);

	glPushMatrix();

	glTranslatef(0, -0.4, 0);

	////////////////////fridge

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

	////////////صراف
	glPushMatrix();
	glRotated(90, 0, 1, 0);
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
	///////////////
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

	glColor4f(0.7, 0.8, 0.9, 0.2);
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

	glColor4f(0.7, 0.8, 0.9, 0.2);
	glBegin(GL_QUADS);
	glVertex3d(5.2, 5, 3);
	glVertex3d(-5.2, 5, 3);
	glVertex3d(-5.2, 5, -3);
	glVertex3d(5.2, 5, -3);
	glEnd();
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

	glColor4f(0.7, 0.8, 0.9, 0.2);
	glBegin(GL_QUADS);
	glVertex3d(8.2, 5, 3);
	glVertex3d(-8.2, 5, 3);
	glVertex3d(-8.2, 5, -3);
	glVertex3d(8.2, 5, -3);
	glEnd();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glEndList();
}

void drawOpDoor()
{
	if (OpDoorOpen)
	{
		if (pos < 2.5)
		{
			pos += 0.07;
		}
	}
	else
	{
		if (pos > 0)
		{
			pos -= 0.07;
		}
	}
	glColor4ub(60, 60, 60, 70);
	glPushMatrix();
	glTranslated(0, 0, pos);
	glTranslated(0, 3.5, 1.75);
	glScaled(0.5, 7, 3.5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, -pos);
	glTranslated(0, 3.5, -1.75);
	glScaled(0.5, 7, -3.5);
	glutSolidCube(1);
	glPopMatrix();
}

void initDoctorRoom()
{
	///////مكتب
	glNewList(35, GL_COMPILE);
	glPushMatrix();
	// walls
	////////////////////////////////////////
	glPushMatrix();

	// windows wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();

	// iner wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(16, 0, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	// outer wall
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	// door wall
	glBegin(GL_QUADS);
	glVertex3f(0, 7, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 7, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 7, 0);
	glVertex3f(2.25, 7, 0);
	glVertex3f(2.25, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(5.75, 0, 0);
	glVertex3f(5.75, 7, 0);
	glVertex3f(16, 7, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	glPopMatrix();
	///////////////////////////////

	glPushMatrix();
	glTranslated(10.5, 1.75, 8);
	glRotated(90, -1, 0, 0);
	glRotated(90, 0, 0, -1);
	glScaled(0.13, 0.13, 0.13);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(59, 59, 59, 255);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1.5, 0, 3);
	glScalef(0.5, 1.5, 0.5);
	glColor4ub(59, 59, 59, 255);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 0, 3.5);
	glScaled(5, -3, 0);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);

	glPopMatrix();

	//	تفاصيل الطابعة

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

	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glEndList();
}

void drawDoctorRoom()
{
	glPushMatrix();
	glCallList(35);
	glTranslated(2.25, 3.5, 0);
	drawDoor();
	glPopMatrix();
}
void initResiption()
{
	glNewList(30, GL_COMPILE);
	glPushMatrix();
	// walls
	////////////////////////////////////////
	glPushMatrix();
	glPushMatrix();

	// windows wall

	// iner wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(16, 0, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();
	glTranslated(-25, 0, 20);
	glRotated(90, 0, 1, 0);
	glScaled(1.25, 1, 1.25);

	// windows wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();

	glPopMatrix();
	///////////////////////////////
	glTranslated(12, 0.8, 6);
	glRotated(90, 0, 1, 0);
	glScaled(0.4, 0.4, 0.4);
	glPushMatrix();
	////////////صراف
	glPushMatrix();
	glRotated(90, 0, 1, 0);
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
	///////////////
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

	glColor4f(0.7, 0.8, 0.9, 0.2);
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

	glColor4f(0.7, 0.8, 0.9, 0.2);
	glBegin(GL_QUADS);
	glVertex3d(5.2, 5, 3);
	glVertex3d(-5.2, 5, 3);
	glVertex3d(-5.2, 5, -3);
	glVertex3d(5.2, 5, -3);
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	for (int i = 0; i < 5; i++)
	{
		// كرسي المكتب

		glPushMatrix();
		glTranslated(1, 3.4, 4);
		glRotated(90, 0, 1, 0);
		glScaled(0.15, 0.12, 0.15);

		// neck
		glColor4ub(100, 100, 100, 255);
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

		glColor4ub(20, 20, 15, 255);
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

		glColor4ub(100, 100, 100, 255);
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

		glColor4ub(20, 20, 15, 255);
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
		glTranslated(0, 0, 2.3);
	}
	glPopMatrix();

	glTranslated(0, 0, 0);
	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();

	glTranslated(-25, 0, 20);
	glRotated(90, 0, 1, 0);
	glScaled(1.25, 1, 1.25);
	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glEndList();
}

void initPatientRoom()
{
	///////
	glNewList(33, GL_COMPILE);
	glPushMatrix();
	// walls
	////////////////////////////////////////
	glPushMatrix();

	// windows wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();

	// iner wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(16, 0, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	// outer wall
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	// door wall
	glBegin(GL_QUADS);
	glVertex3f(0, 7, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 7, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 7, 0);
	glVertex3f(2.25, 7, 0);
	glVertex3f(2.25, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(5.75, 0, 0);
	glVertex3f(5.75, 7, 0);
	glVertex3f(16, 7, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	/// bathroom empty wall
	glBegin(GL_QUADS);
	glVertex3f(8, 0, 8);
	glVertex3f(8, 10, 8);
	glVertex3f(16, 10, 8);
	glVertex3f(16, 0, 8);
	glEnd();

	// batheroom door wall
	glBegin(GL_QUADS);
	glVertex3f(8, 7, 0);
	glVertex3f(8, 10, 0);
	glVertex3f(8, 10, 8);
	glVertex3f(8, 7, 8);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(8, 0, 0);
	glVertex3f(8, 10, 0);
	glVertex3f(8, 10, 2.25);
	glVertex3f(8, 0, 2.25);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(8, 0, 5.75);
	glVertex3f(8, 10, 5.75);
	glVertex3f(8, 10, 8);
	glVertex3f(8, 0, 8);
	glEnd();

	glPopMatrix();

	///////////////////////////////

	// bed
	glPushMatrix();
	glTranslated(11, 0, 16);
	glRotated(90, 0, 1, 0);
	glScaled(2, 2, 2);
	glPushMatrix();
	glTranslated(0, 0.035, 0);
	glPushMatrix();
	glTranslated(0, 1.2, 0);
	glPushMatrix();
	glColor3ub(50, 255, 255);
	glScalef(1, 0.2, 2);
	glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(0, -0.2, 0);
	glScalef(1, 0.1, 2);
	glutSolidCube(2);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(-0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(-0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(30, 30, 30);
	glTranslated(-0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(30, 30, 30);
	glTranslated(0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(30, 30, 30);
	glTranslated(-0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(30, 30, 30);
	glTranslated(0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(0, 1.33, 2);
	glScalef(1, 0.4, 0.05);
	glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(220, 220, 220);
	glTranslated(0, 1.5, 1.6);
	glRotated(-7, 1, 0, 0);
	glScalef(1, 0.2, 0.5);
	glutSolidCube(1.4);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	//// batheroom
	glPushMatrix(); // toilet
	glTranslated(1.5, 0, 6.11);
	glScaled(2, 2, 2);

	glPushMatrix();

	glPushMatrix();

	glTranslated(11, -0.2, -1.5);
	glPushMatrix(); // cylinder up
	glColor3ub(0, 0, 0);
	glTranslated(-6, 0.9, -1);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.2, 0.5, 0.6, 50, 50);
	glPopMatrix();

	glPushMatrix(); // cylinder down
	glColor3ub(0, 0, 0);
	glTranslated(-6, 0.9, -1);
	glRotated(-90, -1, 0, 0);
	gluCylinder(a, 0.2, 0.5, 0.7, 50, 50);
	glPopMatrix();

	glPushMatrix(); // مسند
	glTranslated(-6, 1.5, -1.4);
	glScalef(0.6, 0.8, 0.2);
	glutSolidCube(1.5);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); // bathroom sink
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(5, 0.76, -7);

	glScaled(0.5, 0.5, 0.5);

	glPushMatrix();
	glTranslated(3, -0.35, 13.4);
	glScalef(0.2, 1, 0.4);
	glutSolidCube(2.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(3, 0.8, 13.4);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.6, 1.5, 0.7, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(3.5, 2, 13.25);
	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(3.7, 2.2, 13.25);
	glRotated(90, 0, 0, 1);
	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(7, 1.85, -0.2);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(7, 1.85, -0.55);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	/// table
	glPushMatrix(); // table for patient
	glTranslated(10, 0, 18);
	glRotated(90, 0, 1, 0);
	glScaled(2, 2, 2);
	glPushMatrix();
	glColor3ub(120, 67, 21);
	glScalef(1, 0.2, 0.5);
	glTranslated(2.8, 9.3, 1);
	glScalef(1.2, 1, 1.4);
	glutSolidCube(1.5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(220, 220, 220);
	glTranslatef(3.5, 1.7, 0.55);
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.73, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.25, 0.02, 0.55);
	glRotatef(90, 0, 1, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.35, 0.09, 0.28);
	gluCylinder(a, 0.05, 0.05, 0.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslated(3.5, 0.09, 0.28);
	gluCylinder(a, 0.05, 0.05, 0.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(3.5, 0.01, 0.33);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(3.5, 0.01, 0.75);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(2.35, 0.01, 0.75);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(2.35, 0.01, 0.33);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPopMatrix();

	// sofa
	glPushMatrix();

	glTranslated(4, 4.1, 20);
	glRotated(90, -1, 0, 0);
	glRotated(30, 0, 0, 1);
	glScaled(0.3, 0.3, 0.3);

	glPushMatrix();

	glTranslated(4, 15, -10);
	glScalef(2, 2, 1.2);
	glColor4ub(28, 18, 18, 255);
	glutSolidCube(6);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1, 15, -2.5);
	glScalef(0.5, 2.5, 1.5);
	glColor4ub(28, 18, 18, 255);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(4.6, 20, -6.3);
	glScalef(1.3, 0.5, 0.8);
	glColor4ub(78, 62, 62, 255);
	gluCylinder(a, 4, 4, 3.5, 30, 30);

	glPopMatrix();

	glPushMatrix();

	glTranslated(4.6, 9, -6.3);
	glScalef(1.3, 0.5, 0.8);
	glColor4ub(78, 62, 62, 255);
	gluCylinder(a, 4, 4, 3.5, 30, 30);

	glPopMatrix();

	glPopMatrix();

	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glEndList();
}

void drawPatientRoom()
{
	glPushMatrix();
	glCallList(33);
	/// room door
	glPushMatrix();
	glTranslated(2.25, 3.5, 0);
	drawDoor();
	glPopMatrix();
	/// bathroom door
	glPushMatrix();
	glTranslated(8, 3.5, 2.25);
	glRotated(270, 0, 1, 0);
	drawDoor();
	glPopMatrix();
	glPopMatrix();
}

void initStairs()
{
	glNewList(36, GL_COMPILE);
	glPushMatrix();
	glRotated(180, 0, 1, 0);
	glColor4ub(215.1, 196.6, 169.5, 255);
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

	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(12, 0, 4);
	glVertex3f(12, 10, 4);
	glVertex3f(0, 10, 4);
	glVertex3f(0, 0, 4);
	glEnd();

	glColor4ub(215.1, 196.6, 169.5, 255);
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
	glColor4ub(215.1, 196.6, 169.5, 255);
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

void initCTRoom()
{
	glNewList(32, GL_COMPILE);
	glPushMatrix();
	// walls
	////////////////////////////////////////
	glPushMatrix();

	// windows wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();

	// iner wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(16, 0, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	// outer wall
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	// door wall
	glBegin(GL_QUADS);
	glVertex3f(0, 7, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 7, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 7, 0);
	glVertex3f(2.25, 7, 0);
	glVertex3f(2.25, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(5.75, 0, 0);
	glVertex3f(5.75, 7, 0);
	glVertex3f(16, 7, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	/// room wall
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 12);
	glVertex3f(0, 10, 12);
	glVertex3f(2, 10, 12);
	glVertex3f(2, 0, 12);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(6, 0, 12);
	glVertex3f(6, 10, 12);
	glVertex3f(10.25, 10, 12);
	glVertex3f(10.25, 0, 12);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13.75, 0, 12);
	glVertex3f(13.75, 10, 12);
	glVertex3f(16, 10, 12);
	glVertex3f(16, 0, 12);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(2, 0, 12);
	glVertex3f(2, 2, 12);
	glVertex3f(6, 2, 12);
	glVertex3f(6, 0, 12);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(2, 6, 12);
	glVertex3f(2, 10, 12);
	glVertex3f(6, 10, 12);
	glVertex3f(6, 6, 12);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(10.25, 7, 12);
	glVertex3f(10.25, 10, 12);
	glVertex3f(13.75, 10, 12);
	glVertex3f(13.75, 7, 12);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(8, 0, 12);
	glVertex3f(8, 10, 12);
	glVertex3f(8, 10, 20);
	glVertex3f(8, 0, 20);
	glEnd();
	glPushMatrix();
	glTranslated(4, 4, 12);
	glScaled(1, 1, 0.3);
	glColor4ub(40, 40, 40, 255);
	glutSolidTorus(1, 3, 50, 50);
	glPopMatrix();

	glPopMatrix();
	glPushMatrix();
	glTranslated(4, 0, 12);
	glScaled(1.78, 2.13, 2);
	glCallList(34);
	glPopMatrix();
	///////////////////////////////
	glPushMatrix(); // جهاز الاشعة

	glTranslated(16, -0.1, 5);
	glScaled(2, 2, 2);
	glPushMatrix();
	glColor3ub(40, 100, 200); // تخت
	glTranslated(-2, 1, 0);
	glScaled(1.5, 0.15, 3.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90); // base
	glTranslated(-2, 0.5, 0);
	glRotated(90, 1, 0, 0);
	glScaled(0.3, 0.7, 0.3);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90); // tall cube
	glTranslated(-1.05, 2.3, 0);
	glScaled(0.15, 0.9, 0.2);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0); // شاشة
	glTranslated(-1.5, 2.9, 0);
	glScaled(0.15, 0.2, 0.3);
	glutSolidCube(3);
	glPopMatrix();

	glPopMatrix();
	// window
	glPushMatrix();
	glColor4ub(215.1, 196.6, 169.5, 255); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	glEndList();
}

void drawCTRoom()
{
	glPushMatrix();
	glCallList(32);
	glPushMatrix();
	glTranslated(10.25, 3.5, 12);
	drawDoor();
	glPopMatrix();
	glPushMatrix();
	glTranslated(2.25, 3.5, 0);
	drawDoor();
	glPopMatrix();
	glPopMatrix();
}

void drawPatientRoomsFloor()
{
	// patient rooms floor
	glPushMatrix();
	glColor4ub(14.4, 188.0, 185, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -24);
	glVertex3f(80, 0, -24);
	glVertex3f(80, 0, 24);
	glVertex3f(0, 0, 24);
	glEnd();
	glPushMatrix();
	glPushMatrix();
	glTranslated(0, 0, 4);
	drawDoctorRoom();
	glPopMatrix();
	glPushMatrix();
	glTranslated(20, 0, 4);
	glRotated(90, 0, 1, 0);
	glCallList(36);
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 4);
	glVertex3f(0, 10, 4);
	glVertex3f(0, 10, 12);
	glVertex3f(0, 0, 12);
	glEnd();
	glColor4ub(70, 70, 70, 255);
	glPushMatrix();
	glTranslated(0, 4, 8);
	glScaled(0.2, 8, 6.5);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glPushMatrix();
	glTranslated(32, 0, 4);
	drawPatientRoom();
	glPopMatrix();
	glPushMatrix();
	glTranslated(48, 0, 4);
	drawPatientRoom();
	glPopMatrix();
	glPushMatrix();
	glTranslated(64, 0, 4);
	drawPatientRoom();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	for (int i = 0; i < 5; i++)
	{
		glPushMatrix();
		glTranslated(0, 0, -4);
		glScaled(1, 1, -1);
		drawPatientRoom();
		glPopMatrix();
		glTranslated(16, 0, 0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(-8, 0, 0);
	glScaled(-1, 1, 1);
	glCallList(36);
	glPopMatrix();
	glPopMatrix();
}

void initPharmacy()
{
	glNewList(31, GL_COMPILE);
	// walls
	////////////////////////////////////////
	glPushMatrix();

	// windows wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();

	// iner wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(16, 0, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	// outer wall
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	// door wall
	glBegin(GL_QUADS);
	glVertex3f(0, 7, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 7, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 7, 0);
	glVertex3f(2.25, 7, 0);
	glVertex3f(2.25, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(5.75, 0, 0);
	glVertex3f(5.75, 7, 0);
	glVertex3f(16, 7, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	glPopMatrix();

	glPushMatrix(); // خرازتين1
	glTranslated(16, 7, 5);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, -1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, -1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, 1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, 0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, -0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, 0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, -0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPopMatrix();
	/////////////////////

	glPushMatrix(); // خرازتين1
	glTranslated(16, 7, 7.7);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, -1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, -1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, 1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, 0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, -0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, 0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, -0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPopMatrix();
	/////////////////////

	glPushMatrix(); // خرازتين1
	glTranslated(16, 4.7, 5);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, -1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, -1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, 1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, 0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, -0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, 0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, -0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPopMatrix();
	/////////////////////

	glPushMatrix(); // خرازتين1
	glTranslated(16, 4.7, 7.7);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, -1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, -1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, 1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, 0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, -0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, 0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, -0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPopMatrix();
	/////////////////////
	///////////////////////////////
	glPushMatrix();
	glTranslated(8.5, 1, 10);
	glRotated(90, 0, 1, 0);
	glScaled(-0.4, 0.4, 0.4);
	glCallList(21);
	glPopMatrix();

	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();
	glEndList();
}
void drawPharmacy()
{
	glPushMatrix();
	glCallList(31);
	glTranslated(2.25, 3.5, 0);
	drawDoor();
	glPopMatrix();
}
void initCafeteriaContent()
{
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
}

void initCafeteria()
{
	glNewList(29, GL_COMPILE);
	glPushMatrix();
	glPushMatrix();

	// walls
	////////////////////////////////////////
	glPushMatrix();
	glColor4ub(215.1, 196.6, 169.5, 255);

	// iner wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(32, 0, 20);
	glVertex3f(32, 10, 20);
	glVertex3f(32, 10, 0);
	glVertex3f(32, 0, 0);
	glEnd();


	// windows wall
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();
	glPushMatrix();
	glTranslated(-25, 0, 20);
	glRotated(90, 0, 1, 0);
	glScaled(1.25, 1, 1.25);

	// windows wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();
	glPopMatrix();

	glTranslated(16, 0, 0);

	// windows wall
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();

	

	glPopMatrix();
	///////////////////////////////
	glTranslated(22, 0.9, 12);
	glScaled(0.33, 0.33, 0.33);

	///////////godfather
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
	glPopMatrix();
	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-25, 0, 20);
	glRotated(90, 0, 1, 0);
	glScaled(1.25, 1, 1.25);
	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	glTranslated(16, 0, 0);

	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();

	

	glPopMatrix();
	glEndList();
}

void initOpRoom()
{
	glNewList(28, GL_COMPILE);
	glPushMatrix();
	// walls
	////////////////////////////////////////
	glPushMatrix();

	// windows wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();

	// iner wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(16, 0, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	// door wall
	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 7, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 6.5);
	glVertex3f(0, 10, 6.5);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(0, 10, 13.5);
	glVertex3f(0, 0, 13.5);
	glEnd();

	// corridor wall
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	glPopMatrix();
	///////////////////////////////

	glPushMatrix(); // تخت العمليات
	glTranslated(5, 0.1, 0);
	glScaled(2, 2, 2);
	glPushMatrix();
	glTranslated(5, 0, 5);
	glPushMatrix();
	glColor3ub(0, 0, 0); // تخت
	glTranslated(-2, 1, 0);
	glScaled(1.5, 0.25, 3.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90); // base
	glTranslated(-2, 0.5, 0);
	glScaled(0.3, 0.35, 0.3);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix();			// base
	glColor3ub(90, 90, 90); // base
	glTranslated(-2.1, -0.1, 0);
	glScaled(0.4, 0.08, 0.6);
	glutSolidCube(3);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(13, 0, 20);
	glRotated(80, 0, 1, 0);
	glScaled(2, 2, 2);
	glPushMatrix(); // surgery table with tools
	glTranslated(2, 0.05, -1);

	glPushMatrix();
	glColor3ub(90, 90, 90); // base
	glTranslated(1, 0.1, -3);
	glScaled(0.4, 0.03, 0.6);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(1.5, 1.5, -2.2);
	glRotated(90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(1.5, -0.05, -2.2);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(0.5, 1.5, -2.2);
	glRotated(90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(0.5, -0.05, -2.2);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(0.5, 1.5, -3.8);
	glRotated(90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(0.5, -0.05, -3.8);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(1.5, 1.5, -3.8);
	glRotated(90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(1.5, -0.05, -3.8);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix(); // up
	glColor3ub(100, 150, 255);
	glTranslated(1, 1.5, -3);
	glScaled(0.4, 0.03, 0.6);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix();
	glPushMatrix(); // ملقط
	glColor3ub(90, 90, 90);
	glTranslated(1, 1.56, -3.2);
	glRotated(100, 0, 1, 0);
	gluCylinder(a, 0.007, 0.007, 0.2, 50, 50);
	glPopMatrix();
	glPushMatrix(); // ملقط
	glColor3ub(90, 90, 90);
	glTranslated(1, 1.56, -3.2009);
	glRotated(80, 0, 1, 0);
	gluCylinder(a, 0.007, 0.007, 0.2, 50, 50);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glPushMatrix(); // مقص
	glColor3ub(90, 90, 90);
	glTranslated(1, 1.56, -3);
	glRotated(105, 0, 1, 0);
	gluCylinder(a, 0.007, 0.007, 0.2, 50, 50);
	glPopMatrix();
	glPushMatrix(); // مقص
	glColor3ub(90, 90, 90);
	glTranslated(1, 1.56, -3.03);
	glRotated(75, 0, 1, 0);
	gluCylinder(a, 0.007, 0.007, 0.2, 50, 50);
	glPopMatrix();
	glPushMatrix(); // دويرة المقص
	glColor3ub(90, 90, 90);
	glTranslated(1.02, 1.56, -2.987);
	glRotated(100, 0, 1, 0);
	gluSphere(a, 0.02, 50, 50);
	glPopMatrix();
	glPushMatrix(); // دويرةالمقص
	glColor3ub(90, 90, 90);
	glTranslated(1.02, 1.56, -3.04);
	glRotated(80, 0, 1, 0);
	gluSphere(a, 0.02, 50, 50);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glPushMatrix(); // 2ملقط
	glColor3ub(90, 90, 90);
	glTranslated(1, 1.56, -2.8);
	glRotated(100, 0, 1, 0);
	gluCylinder(a, 0.007, 0.007, 0.2, 50, 50);
	glPopMatrix();
	glPushMatrix(); // 2ملقط
	glColor3ub(90, 90, 90);
	glTranslated(1, 1.56, -2.8009);
	glRotated(80, 0, 1, 0);
	gluCylinder(a, 0.007, 0.007, 0.2, 50, 50);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(1, 1.56, -2.6);
	glRotated(90, 0, 1, 0);
	gluCylinder(a, 0.007, 0.007, 0.2, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glPushMatrix(); // مقص
	glColor3ub(90, 90, 90);
	glTranslated(1, 1.56, -3.4);
	glRotated(105, 0, 1, 0);
	gluCylinder(a, 0.007, 0.007, 0.2, 50, 50);
	glPopMatrix();
	glPushMatrix(); // مقص
	glColor3ub(90, 90, 90);
	glTranslated(1, 1.56, -3.43);
	glRotated(75, 0, 1, 0);
	gluCylinder(a, 0.007, 0.007, 0.2, 50, 50);
	glPopMatrix();
	glPushMatrix(); // دويرة المقص
	glColor3ub(90, 90, 90);
	glTranslated(1.02, 1.56, -3.387);
	glRotated(100, 0, 1, 0);
	gluSphere(a, 0.02, 50, 50);
	glPopMatrix();
	glPushMatrix(); // دويرةالمقص
	glColor3ub(90, 90, 90);
	glTranslated(1.02, 1.56, -3.44);
	glRotated(80, 0, 1, 0);
	gluSphere(a, 0.02, 50, 50);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glEndList();
}

void drawOpRoom()
{
	glPushMatrix();
	glCallList(28);
	glTranslated(0, 0, 10);
	drawOpDoor();
	glPopMatrix();
}

void initPrepationRoom()
{
	glNewList(26, GL_COMPILE);
	// walls
	////////////////////////////////////////
	glPushMatrix();

	// windows wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();

	// outer wall
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	// door wall
	glBegin(GL_QUADS);
	glVertex3f(0, 7, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 7, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 7, 0);
	glVertex3f(2.25, 7, 0);
	glVertex3f(2.25, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(5.75, 0, 0);
	glVertex3f(5.75, 7, 0);
	glVertex3f(16, 7, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	glPopMatrix();

	/////////////////////////////////////////////////
	glPushMatrix();
	glTranslated(15.2, 0, 26);
	glRotated(90, 0, -1, 0);
	glScaled(2, 2, 2);
	glPushMatrix();
	glPushMatrix(); // خرازتين1
	glTranslated(-3, 1, 1);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, -1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, -1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, 1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, 0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, -0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, 0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, -0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPopMatrix();

	/////////////////////////////////////////////////////////////////////////

	glPushMatrix(); // 2خرازتين
	glTranslated(-3, 1, 3.5);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, -1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, -1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, 1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, 0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, -0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, 0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, -0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix(); // مغسلة
	glColor3ub(90, 90, 90);
	glTranslated(-1, 0.75, 0);
	glRotated(-90, 1, 0, 0);
	glScaled(0.5, 0.5, 0.5);
	gluCylinder(a, 0.6, 1.5, 0.7, 50, 50);
	glPopMatrix();

	glPushMatrix(); // حنفية

	glTranslated(0, -0.2, 0);
	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(-0.01, 1.5, 0);
	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(-0.22, 1.7, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(-0.01, 1.35, -0.2);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(-0.01, 1.35, 0.2);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glPushMatrix(); // خرازتين 3
	glTranslated(-3, 1, 6);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, -1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, -1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, 1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // باب مفتوح
	glTranslated(-3.2, 0, 0.57);
	glRotated(60, 0, 1, 0);
	glPushMatrix();
	glColor3ub(90, 90, 90);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glColor3ub(166, 157, 0);
	glTranslated(-0.2, 0, -1);
	glScalef(0.1, 1.2, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(166, 157, 0);
	glTranslated(-0.1, 0.6, -1);
	glRotated(90, 0, 0, 1);
	glScalef(0.1, 0.3, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(166, 157, 0);
	glTranslated(-0.1, -0.6, -1);
	glRotated(90, 0, 0, 1);
	glScalef(0.1, 0.3, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // صينية
	glColor3ub(100, 150, 255);
	glTranslated(-1, -0.5, 0);
	glScaled(0.4, 0.03, 0.6);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix(); // صينية
	glColor3ub(100, 150, 255);
	glTranslated(-1, 0.5, 0);
	glScaled(0.4, 0.03, 0.6);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix(); // صينية
	glColor3ub(100, 150, 255);
	glTranslated(-1, 0, 0);
	glScaled(0.4, 0.03, 0.6);
	glutSolidCube(3);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	/////////////////////////////////////////////////

	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();
	glEndList();
}

void drawPrepationRoom()
{
	glPushMatrix();
	glCallList(26);
	glTranslated(2.25, 3.5, 0);
	drawDoor();
	glPopMatrix();
}

void initLab()
{
	glNewList(25, GL_COMPILE);
	// walls
	////////////////////////////////////////
	glPushMatrix();

	// windows wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();

	// iner wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(16, 0, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	// outer wall
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	// door wall
	glBegin(GL_QUADS);
	glVertex3f(0, 7, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 7, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 7, 0);
	glVertex3f(2.25, 7, 0);
	glVertex3f(2.25, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(5.75, 0, 0);
	glVertex3f(5.75, 7, 0);
	glVertex3f(16, 7, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	glPopMatrix();

	/////////////////////////////////////////////////
	glPushMatrix();
	glTranslated(15.2, 0, 26);
	glRotated(90, 0, -1, 0);
	glScaled(2, 2, 2);
	glPushMatrix();
	glPushMatrix(); // خرازتين1
	glTranslated(-3, 1, 1);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, -1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, -1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, 1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, 0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, -0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, 0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, -0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPopMatrix();

	/////////////////////////////////////////////////////////////////////////

	glPushMatrix(); // 2خرازتين
	glTranslated(-3, 1, 3.5);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, -1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, -1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, 1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, 0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(245, 245, 220);
	glTranslated(-2.2, 0, -0.65);
	glScaled(0.2, 2.2, 1.27);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, 0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-2.37, 0, -0.13);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix(); // مغسلة
	glColor3ub(90, 90, 90);
	glTranslated(-1, 0.75, 0);
	glRotated(-90, 1, 0, 0);
	glScaled(0.5, 0.5, 0.5);
	gluCylinder(a, 0.6, 1.5, 0.7, 50, 50);
	glPopMatrix();

	glPushMatrix(); // حنفية

	glTranslated(0, -0.2, 0);
	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(-0.01, 1.5, 0);
	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(-0.22, 1.7, 0);
	glRotated(90, 0, 0, 1);
	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(-0.01, 1.35, -0.2);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(90, 90, 90);
	glTranslated(-0.01, 1.35, 0.2);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glPushMatrix(); // خرازتين 3
	glTranslated(-3, 1, 6);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, -1, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, -1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-1, 0, 1.2);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 2.2, 2.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // باب مفتوح
	glTranslated(-3.2, 0, 0.57);
	glRotated(60, 0, 1, 0);
	glPushMatrix();
	glColor3ub(90, 90, 90);
	glScaled(0.2, 2.2, 2.5);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glColor3ub(166, 157, 0);
	glTranslated(-0.2, 0, -1);
	glScalef(0.1, 1.2, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(166, 157, 0);
	glTranslated(-0.1, 0.6, -1);
	glRotated(90, 0, 0, 1);
	glScalef(0.1, 0.3, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(166, 157, 0);
	glTranslated(-0.1, -0.6, -1);
	glRotated(90, 0, 0, 1);
	glScalef(0.1, 0.3, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // صينية
	glColor3ub(100, 150, 255);
	glTranslated(-1, -0.5, 0);
	glScaled(0.4, 0.03, 0.6);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix(); // صينية
	glColor3ub(100, 150, 255);
	glTranslated(-1, 0.5, 0);
	glScaled(0.4, 0.03, 0.6);
	glutSolidCube(3);
	glPopMatrix();

	glPushMatrix(); // صينية
	glColor3ub(100, 150, 255);
	glTranslated(-1, 0, 0);
	glScaled(0.4, 0.03, 0.6);
	glutSolidCube(3);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -1);
	glRotated(90, 0, 0, 0);
	glScaled(2, 2, 2);
glPushMatrix();
glColor3ub(0, 0, 0);
glTranslated(-2, 1, 1);
glScaled(0.3,0.05,0.3);
glutSolidCube(2);
glPopMatrix();

glPushMatrix();
glColor3ub(0, 0, 0);
glTranslated(-2, 1.3, 1);
glScaled(0.3, 0.05, 0.3);
glutSolidCube(2);
glPopMatrix();

glPushMatrix();
glColor3ub(129, 127, 38);
glTranslated(-1.8, 1.5, 1);
glScalef(0.1, 1, 0.1);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor3ub(129, 127, 38);
glTranslated(-1.95, 2, 1);
glRotated(90, 0, 0, 1);
glScalef(0.1, 0.4, 0.1);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor3ub(129, 127, 38); 
glTranslated(-2.1, 1.85, 1);
glScalef(0.1, 0.2, 0.1);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor3ub(192, 192, 192);
glTranslated(-2.1, 1.7, 1);
glScaled(0.2, 0.05, 0.2);
glutSolidCube(2);
glPopMatrix();

glPushMatrix();
glColor3ub(129, 127, 38); 
glTranslated(-2.1, 1.65, 1);
glRotated(120,1,0,0);
gluCylinder(a,0.02,0.02,0.17,50,50);
glPopMatrix();

glPushMatrix();
glColor3ub(129, 127, 38);
glTranslated(-2.1, 1.65, 1);
glRotated(60, 1, 0, 0);
gluCylinder(a, 0.02, 0.02, 0.17, 50, 50);
glPopMatrix();

glPopMatrix();

	glPopMatrix();
	/////////////////////////////////////////////////

	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();
	glEndList();
}

void drawLab()
{
	glPushMatrix();
	glCallList(25);
	glTranslated(2.25, 3.5, 0);
	drawDoor();
	glPopMatrix();
}

void drawGroundFloor()
{
	glColor4ub(14.4, 188.0, 185, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -24);
	glVertex3f(80, 0, -24);
	glVertex3f(80, 0, 24);
	glVertex3f(0, 0, 24);
	glEnd();

	glPushMatrix();
	glTranslated(48, 0, -4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, -1);
	drawPrepationRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslated(64, 0, -4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, -1);
	drawOpRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslated(64, 0, 4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, 1);
	drawLab();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 4);
	glCallList(30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -4);
	glScaled(1, 1, -1);
	glCallList(29);
	glPopMatrix();

	glPushMatrix();
	glTranslated(20, 0, 4);
	glRotated(90, 0, 1, 0);
	glScaled(1, 1, 1);
	glCallList(36);
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 4);
	glVertex3f(0, 10, 4);
	glVertex3f(0, 10, 12);
	glVertex3f(0, 0, 12);
	glEnd();
	glColor4ub(70, 70, 70, 255);
	glPushMatrix();
	glTranslated(0, 4, 8);
	glScaled(0.2, 8, 6.5);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(32, 0, 4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, 1);
	drawDoctorRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslated(48, 0, 4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, 1);
	drawCTRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslated(32, 0, -4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, -1);
	drawPharmacy();
	glPopMatrix();


	glPushMatrix();
	glTranslated(72, 0, 0);
	glScaled(-1, 1, 1);
	glCallList(36);
	glPopMatrix();
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	GLfloat am[] = {0.4, 0.4, 0.4, 0.5};
	glLightfv(GL_LIGHT0, GL_AMBIENT, am);
	GLfloat di[] = {0.8, 0.8, 0.8, 0.5};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, di);
	GLfloat sp[] = {0.9, 0.9, 0.9, 0.5};
	glLightfv(GL_LIGHT0, GL_SPECULAR, sp);			   // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	loadSkyboxTexture();
	initDoor();
	initTree();
	initAmbulance();
	initCounter();
	initStairs();
	initDoctorRoom();
	initPatientRoom();
	initBed();
	initCTRoom();
	initPharmacy();
	initResiption();
	initCafeteriaContent();
	initCafeteria();
	initOpRoom();
	initPrepationRoom();
	initLab();
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("OpenGL Error: %s\n", gluErrorString(error));
	}
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

	if (light)
	{
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}
	if (lighting)
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat position[] = {0, 1000, 0, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	gluLookAt(Ex, E + 5, Ez, Ex + cos(th), E + 5, Ez + sin(th), 0, 1, 0);
	GLUquadricObj *a = gluNewQuadric();
	if (rotate)
	{
		glRotated(90, 0, 0, 1);
	}

	drawSkybox();

	/////////////////////////////////////////////////////////////////
	glPushMatrix();
	glPushMatrix();
	glTranslated(-20, 0, 15);
	glCallList(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-10, 0, -20);
	glCallList(24);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, 0, -18);
	glCallList(24);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-34, 0, -21);
	glCallList(24);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-10, 0, -11);
	glCallList(24);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-23, 0, -8);
	glCallList(24);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-34, 0, -10);
	glCallList(24);
	glPopMatrix();

	glColor4ub(77, 119, 71, 255);
	glBegin(GL_QUADS);
	glVertex3f(-40, -0.0001, -24);
	glVertex3f(-40, -0.0001, 24);
	glVertex3f(0, -0.0001, 24);
	glVertex3f(0, -0.0001, -24);
	glEnd();
	glColor4ub(90, 90, 90, 255);
	glBegin(GL_QUADS);
	glVertex3f(-40, 0, -3);
	glVertex3f(-40, 0, 3);
	glVertex3f(0, 0, 3);
	glVertex3f(0, 0, -3);
	glEnd();
	glColor4ub(100, 100, 100, 255);
	glBegin(GL_QUADS);
	glVertex3f(-35, 0, 23);
	glVertex3f(-35, 0, 4);
	glVertex3f(-10, 0, 4);
	glVertex3f(-10, 0, 23);
	glEnd();
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 7, -4);
	glVertex3f(0, 7, 4);
	glVertex3f(0, 50, 4);
	glVertex3f(0, 50, -4);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, 7, -4);
	glVertex3f(0, 7, -3.5);
	glVertex3f(0, 0, -3.5);
	glVertex3f(0, 0, -4);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, 7, 3.5);
	glVertex3f(0, 7, 4);
	glVertex3f(0, 0, 4);
	glVertex3f(0, 0, 3.5);
	glEnd();
	glPopMatrix();
	drawGroundFloor();
	glTranslated(0, 10, 0);
	for(int i = 0; i<4; i++) {
	drawPatientRoomsFloor();
	glTranslated(-80, 10, 0);
	}
	glColor4ub(14.4, 188.0, 185, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -24);
	glVertex3f(80, 0, -24);
	glVertex3f(80, 0, 24);
	glVertex3f(0, 0, 24);
	glEnd();
	glTranslated(0, -50, 0);
	drawOpDoor();



	printFPS();
	glutSwapBuffers();
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Use single display buffer.
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("hospital");
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
double r = 0;
double r2 = 0;
int oldTimeSinceStart = 0;src/mainwindow.cpp
int timeSinceStart;
int deltaTime;
bool doorOpen = false;
bool chairTableOpen = false;
bool sprinting = false;
bool phisics = false;
double acciliration = -0.08;
double velocity = 0;
bool light = false;
bool lighting = false;
GLuint skyboxTextures[6];
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
	case 'l':
		if (light)
			light = false;
		else
			light = true;
		break;
	case 'L':
		if (lighting)
			lighting = false;
		else
			lighting = true;
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
			velocity += 0.9;
		}
		break;
	case 'd':
		if (sprinting)
		{
			Ex = Ex + 5 * sin(th);
			Ez = Ez + 5 * cos(th);
		}
		else
		{
			Ex = Ex + 2 * sin(th);
			Ez = Ez + 2 * cos(th);
		}
		break;
	case 'a':
		if (sprinting)
		{
			Ex = Ex - 5 * sin(th);
			Ez = Ez - 5 * cos(th);
		}
		else
		{
			Ex = Ex - 2 * sin(th);
			Ez = Ez - 2 * cos(th);
		}
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

void loadSkyboxTextures()
{
    const char *skyboxFileNames[6] = {
        "/home/mohamed/Documents/vscode/c++/obada/texture/skybox_front.jpg",
        "/home/mohamed/Documents/vscode/c++/obada/texture/skybox_back.jpg",
        "/home/mohamed/Documents/vscode/c++/obada/texture/skybox_left.jpg",
        "/home/mohamed/Documents/vscode/c++/obada/texture/skybox_right.jpg",
        "/home/mohamed/Documents/vscode/c++/obada/texture/skybox_top.jpg",
        "/home/mohamed/Documents/vscode/c++/obada/texture/skybox_bottom.jpg"};

    for (int i = 0; i < 6; i++)
    {
        skyboxTextures[i] = SOIL_load_OGL_texture(
            skyboxFileNames[i],
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

        if (!skyboxTextures[i])
        {
            printf("Skybox texture loading failed for %s: %s\n", skyboxFileNames[i], SOIL_last_result());
        }
        else
        {
            printf("Skybox texture loaded successfully: %s\n", skyboxFileNames[i], SOIL_last_result());
        }
    }
}

void drawSkybox()
{
    glEnable(GL_TEXTURE_2D);

    // Draw the skybox cube (size can be adjusted)
    glBegin(GL_QUADS);

    // Front face
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[0]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-100, -100, -100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(100, -100, -100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(100, 100, -100);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-100, 100, -100);

    // Back face
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[1]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(100, -100, 100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-100, -100, 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-100, 100, 100);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(100, 100, 100);

    // Left face
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[2]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-100, -100, -100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-100, -100, 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-100, 100, 100);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-100, 100, -100);

    // Right face
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[3]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(100, -100, -100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(100, -100, 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(100, 100, 100);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(100, 100, -100);

    // Top face
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[4]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-100, 100, -100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(100, 100, -100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(100, 100, 100);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-100, 100, 100);

    // Bottom face
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[5]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-100, -100, 100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(100, -100, 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(100, -100, -100);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-100, -100, -100);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void initMeetingChair()
{
	glPushMatrix();
	glNewList(99, GL_COMPILE);
	GLUquadric *a = gluNewQuadric();
	glColor4ub(100, 100, 100, 255);
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
	gluCylinder(a, 3, 3, 12, 50, 50);
	glPopMatrix();

	glColor4ub(20, 20, 15, 255);
	// base
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(0.6, 3.7, 50, 50);
	glPopMatrix();

	// back
	glPushMatrix();
	glRotatef(-5, 1, 0, 0);
	glScalef(1, 1.3, 0.4);
	gluSphere(a, 7, 50, 50);
	glPopMatrix();

	glColor4ub(100, 100, 100, 255);
	// arms
	glPushMatrix();
	glTranslatef(5, -14, 4);
	glRotatef(-90, 1, -0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -14, 4);
	glRotatef(-90, 1, 0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 50, 50);
	glPopMatrix();

	glColor4ub(20, 20, 15, 255);
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 50, 50);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 50, 50);
	glPopMatrix();

	glEndList();
	glPopMatrix();
}
void initMeetingTable()
{
	glPushMatrix();
	glNewList(5, GL_COMPILE);
	GLUquadric *a = gluNewQuadric();
	glColor4ub(60, 45, 15, 255);

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
	glColor4ub(30, 30, 30, 255);
	glPushMatrix();
	glTranslatef(0, 0.08, 0);
	glScalef(1.5, 0.1, 1);
	glutSolidCube(3);
	glPopMatrix();

	glEndList();
	glPopMatrix();
}

void initBed()
{
	glNewList(34, GL_COMPILE);
	glPushMatrix();
	glPushMatrix();
	glTranslated(0, 0.035, 0);
	glPushMatrix();
	glTranslated(0, 1.2, 0);
	glPushMatrix();
	glColor4ub(50, 255, 255, 255);
	glScalef(1, 0.2, 2);
	glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(0, -0.2, 0);
	glScalef(1, 0.1, 2);
	glutSolidCube(2);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(-0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(-0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.2, 50, 50);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glColor4ub(30, 30, 30, 255);
	glTranslated(-0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(30, 30, 30, 255);
	glTranslated(0.9, 0, -1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(30, 30, 30, 255);
	glTranslated(-0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(30, 30, 30, 255);
	glTranslated(0.9, 0, 1.9);
	glRotated(-90, 1, 0, 0);
	gluSphere(a, 0.07, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(100, 100, 100, 255);
	glTranslated(0, 1.33, 2);
	glScalef(1, 0.4, 0.05);
	glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(220, 220, 220, 255);
	glTranslated(0, 1.5, 1.6);
	glRotated(-7, 1, 0, 0);
	glScalef(1, 0.2, 0.5);
	glutSolidCube(1.4);
	glPopMatrix();
	glPopMatrix();
	glEndList();
}

/*
void drewMeetingTable()
{
	GLUquadric *a = gluNewQuadric();
	glColor4ub(250, 0, 0, 255);
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
*/

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
	std::cout << '\r' << 1000 / deltaTime << " " << Ex << " " << E << " " << Ez << std::flush;
}

void testCollision()
{
	if (E < 0)
	{
		E = 0;
		velocity = 0;
	}

	if (E < 10 && E > 8 && velocity < 0)
	{
		E = 10;
		velocity = 0;
	}
}

void doPhisics()
{
	velocity += acciliration;
	E += velocity;

	testCollision();
}

void initDoor()
{
	glPushMatrix();
	GLUquadric *a = gluNewQuadric();

	// doors
	glPushMatrix();
	glNewList(6, GL_COMPILE);
	glPushMatrix();
	glColor4ub(175, 125, 51, 255);
	glTranslatef(1.75, 0, 0);
	glScaled(1, 2, 0.08);
	glutSolidCube(3.5);
	glPopMatrix();
	glPushMatrix();
	glColor4ub(220, 186, 136, 255);
	glTranslated(3.2, 0, -0.5);
	gluCylinder(a, 0.17, 0.17, 1, 30, 30);
	gluDisk(a, 0, 0.17, 30, 30);
	glTranslated(0, 0, 1);
	gluDisk(a, 0, 0.17, 30, 30);
	glPopMatrix();
	glEndList();
	glPopMatrix();
}

void drawDoor()
{
	if (doorOpen)
	{
		if (r2 > -90)
		{
			r2 -= deltaTime / 30.0;
		}
	}
	else
	{
		if (r2 < 0)
		{
			r2 += deltaTime / 30.0;
		}
	}
	// glRotatef(90, 1, 0, 0);

	glPushMatrix();
	glRotatef(r2, 0, 1, 0);
	glCallList(6);
	glPopMatrix();
}

void initDoctorRoom()
{
	///////مكتب
	glNewList(35, GL_COMPILE);
	glPushMatrix();
	// walls
	////////////////////////////////////////
	glPushMatrix();

	// windows wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();

	// iner wall
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(16, 0, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	// outer wall
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	// door wall
	glBegin(GL_QUADS);
	glVertex3f(0, 7, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 7, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 7, 0);
	glVertex3f(2.25, 7, 0);
	glVertex3f(2.25, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(5.75, 0, 0);
	glVertex3f(5.75, 7, 0);
	glVertex3f(16, 7, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	glPopMatrix();
	///////////////////////////////

	glPushMatrix();
	glTranslated(10.5, 1.75, 8);
	glRotated(90, -1, 0, 0);
	glRotated(90, 0, 0, -1);
	glScaled(0.13, 0.13, 0.13);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(59, 59, 59, 255);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1.5, 0, 3);
	glScalef(0.5, 1.5, 0.5);
	glColor4ub(59, 59, 59, 255);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 0, 3.5);
	glScaled(5, -3, 0);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);

	glPopMatrix();

	//	تفاصيل الطابعة

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

	// window
	glPushMatrix();
	glColor4ub(95, 178, 252, 60); // Set color with alpha value (128 for 50% transparency)
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glEndList();
}

void drawDoctorRoom()
{
	glPushMatrix();
	glCallList(35);
	glTranslated(2.25, 3.5, 0);
	drawDoor();
	glPopMatrix();
}

void initStairs()
{
	glNewList(36, GL_COMPILE);
	glPushMatrix();
	glRotated(180, 0, 1, 0);
	glColor3f(0, 0, 0);
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

/*
void initsaralists()
{
	glPushMatrix();
	glNewList(1, GL_COMPILE);
	// chairs
	glPushMatrix();
	glTranslated(1, 0, 0.8);

	glPushMatrix();
	glColor4ub(0, 0, 255, 255);
	glScaled(1, 0.1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotated(90, 1, 0, 0);
	glTranslated(0.2, 0.2, 0.2);
	glScaled(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotated(90, 1, 0, 0);
	glTranslatef(-0.2, 0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.2, -0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.2, -0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(0, 0, 255, 255);
	glTranslated(0.2, 0.46, 0);
	glRotated(90, 0, 0, 1);
	glScalef(1, 0.1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslated(0.2, 0.2, -0.12);
	glScalef(0.01, 0.1, 0.4);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
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
	glColor4ub(0, 0, 255, 255);
	glScalef(1, 0.1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.2, 0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.2, 0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.2, -0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.2, -0.2, 0.2);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(0, 0, 255, 255);
	glTranslated(0.2, 0.46, 0);
	glRotated(90, 0, 0, 1);
	glScalef(1, 0.1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslated(0.2, 0.2, -0.12);
	glScalef(0.01, 0.1, 0.4);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.2, -0.2, -0.12);
	glScalef(0.01, 0.1, 0.4);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();

	// table
	glTranslatef(0, 0.4, 0);
	glPushMatrix();

	glColor4ub(46, 128, 168, 255);
	glScalef(1, 0.1, 1.5);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.45, 1.2, 0.45);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.45, 1.2, 0.45);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.45, -1.2, 0.45);
	glScalef(0.1, 0.1, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(195, 200, 200, 255);
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
	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(150, 201, 226, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.5, 0);
	glScalef(0, 0.1, 0.5);
	glColor4ub(123, 123, 123, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.5, 0);
	glScalef(0, 0.1, 0.5);
	glColor4ub(123, 123, 123, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 0.26);
	glScalef(0.01, 1.06, 0.05);
	glColor4ub(123, 123, 123, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -0.26);
	glScalef(0.01, 1.06, 0.05);
	glColor4ub(123, 123, 123, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
	glEndList();

	glNewList(2, GL_COMPILE);

	glColor4ub(245, 241, 185, 255);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();

	glColor4ub(245, 241, 185, 255);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, 10.0f);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glEnd();

	glColor4ub(245, 241, 185, 255);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glVertex3f(-10.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 0.0f, 10.0f);
	glEnd();

	glColor4ub(245, 241, 185, 255);
	glBegin(GL_QUADS);
	glVertex3f(-3.0f, 0.0f, 10.0f);
	glVertex3f(-3.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();

	glColor4ub(245, 241, 185, 255);
	glBegin(GL_QUADS);
	glVertex3f(-6.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 5.0f, 10.0f);
	glVertex3f(-3.0f, 5.0f, 10.0f);
	glVertex3f(-3.0f, 7.0f, 10.0f);
	glEnd();

	glColor4ub(245, 241, 185, 255);
	glBegin(GL_QUADS);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();
	////////////////////////////////////////////////////////////////////////////
	glPushMatrix();
	glScalef(1, 0, 1);
	glColor4ub(130, 130, 130, 255);
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
	glColor4ub(0, 0, 255, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glScalef(1, 0, 0.8);
	glColor4ub(46, 128, 168, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.4, 0);
	glRotated(90, 0, 0, 1);
	glScalef(1, 0, 0.8);
	glColor4ub(46, 128, 168, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, 0.1, 0.4);
	glRotated(90, 1, 0, 0);
	glScalef(0.5, 0, 0.8);
	glColor4ub(46, 128, 168, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, -0.5, 0.4);
	glRotated(90, 1, 0, 0);
	glScalef(0.5, 0, 0.8);
	glColor4ub(46, 128, 168, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, 0.1, -0.4);
	glRotated(90, 1, 0, 0);
	glScalef(0.5, 0, 0.8);
	glColor4ub(46, 128, 168, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, -0.5, -0.4);
	glRotated(90, 1, 0, 0);
	glScalef(0.5, 0, 0.8);
	glColor4ub(46, 128, 168, 255);
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
	glColor4ub(0, 0, 0, 255);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.2, -0.65, 0.2);
	glScaled(0.2, 0.5, 0.2);
	glColor4ub(0, 0, 0, 255);
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
	glColor4ub(245, 241, 185, 255);
	glTranslatef(416, 0, -71);
	glBegin(GL_QUADS);
	glVertex3f(-25.0f, 0.0f, -120.0f);
	glVertex3f(-25.0f, 38.5f, -120.0f);
	glVertex3f(120.0f, 38.5f, -120.0f);
	glVertex3f(120.0f, 0.0f, -120.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(245, 241, 185, 255);
	glTranslatef(361, 0, -123);
	glBegin(GL_QUADS);
	glVertex3f(30.0f, 0.0f, -30.0f);
	glVertex3f(30.0f, 38.5f, -30.0f);
	glVertex3f(30.0f, 38.5f, 30.0f);
	glVertex3f(30.0f, 0.0f, 30.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(245, 241, 190, 255);
	glTranslatef(431, 0, -90);
	glBegin(GL_QUADS);
	glVertex3f(105.0f, 0.0f, -105.0f);
	glVertex3f(105.0f, 38.5f, -105.0f);
	glVertex3f(105.0f, 38.5f, 105.0f);
	glVertex3f(105.0f, 0.0f, 105.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4ub(245, 241, 185, 255);
	glTranslatef(371, 0, -28);
	glBegin(GL_QUADS);
	glVertex3f(43.0f, 0.0f, -43.0f);
	glVertex3f(43.0f, 38.5f, -43.0f);
	glVertex3f(43.0f, 38.5f, 43.0f);
	glVertex3f(43.0f, 0.0f, 43.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(245, 241, 185, 255);
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
*/

void InitGL(void)
{
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	// glClearColor(1.0f, 1.0f, 1.0f, 0.5f);				// Black Background
	// glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	GLfloat am[] = {0.4, 0.4, 0.4, 0.5};
	glLightfv(GL_LIGHT0, GL_AMBIENT, am);
	GLfloat di[] = {0.8, 0.8, 0.8, 0.5};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, di);
	GLfloat sp[] = {0.9, 0.9, 0.9, 0.5};
	glLightfv(GL_LIGHT0, GL_SPECULAR, sp);			   // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	loadSkyboxTextures();
	initDoor();
	initStairs();
	initDoctorRoom();
	initBed();
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

	if (light)
	{
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}
	if (lighting)
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat position[] = {0, 1000, 0, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	gluLookAt(Ex, E + 5, Ez, Ex + cos(th), E + 5, Ez + sin(th), 0, 1, 0);
	GLUquadricObj *a = gluNewQuadric();
	if (phisics)
	{
		doPhisics();
	}

	drawSkybox();

	// glRotated(90, 0, 0, 1);

	/////////////////////////////////////////////////////////////////
	/*
	// fist staircase
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(130, 130, 130, 255);
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
	glColor4ub(130, 130, 130, 255);
	glutSolidCube(20);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////


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
	glColor4ub(245, 241, 185, 255);
	glTranslatef(250.39, 0, -104.3);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -40.0f);
	glVertex3f(-10.0f, 38.5f, -40.0f);
	glVertex3f(40.0f, 38.5f, -40.0f);
	glVertex3f(40.0f, 0.0f, -40.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(245, 141, 0, 255);
	glTranslatef(308, 0, -144);
	glScaled(0.3, 76.5, 0.7);
	glutSolidCube(1);
	glPopMatrix();

	////////////////////////////////////////////////////////////////////////


	// wall left
	glPushMatrix();
	glColor4ub(245, 241, 185, 255);

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
	glColor4ub(245, 241, 190, 255);
	glTranslatef(454.6, 0, 90);
	glBegin(GL_QUADS);
	glVertex3f(105.0f, 0.0f, -105.0f);
	glVertex3f(105.0f, 38.5f, -105.0f);
	glVertex3f(105.0f, 38.5f, 105.0f);
	glVertex3f(105.0f, 0.0f, 105.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4ub(245, 241, 190, 255);
	glTranslatef(368, 0, 38);
	glBegin(GL_QUADS);
	glVertex3f(23.0f, 0.0f, -23.0f);
	glVertex3f(23.0f, 38.5f, -23.0f);
	glVertex3f(23.0f, 38.5f, 23.0f);
	glVertex3f(23.0f, 0.0f, 23.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4ub(245, 241, 190, 255);
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
	glColor4ub(245, 241, 190, 255);
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
	glColor4ub(245, 241, 190, 255);
	glBegin(GL_QUADS);
	glVertex3f(-5.7f, 0.0f, -7.0f);
	glVertex3f(-5.7f, 7.0f, -7.0f);
	glVertex3f(7.0f, 7.0f, -7.0f);
	glVertex3f(7.0f, 0.0f, -7.0f);
	glEnd();
	glPopMatrix();

	glPopMatrix();

	//////////////////////////
	glPushMatrix();
	glColor4ub(245, 241, 190, 255);
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
	glColor4ub(130, 130, 130, 255);
	glutSolidCube(200);

	glPopMatrix();

	glPushMatrix();
	glTranslated(137, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37, 19.5, -100);
	glRotated(90, 0, 1, 0);
	glScalef(0, 5, 22.2);
	glColor4ub(125, 156, 159, 255);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-63, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(13.33);
	glPopMatrix();

	/// سقف
	glPushMatrix();
	glTranslated(37, 41, 0);
	glScalef(1, 0, 1);
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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


	glColor4ub(59, 59, 59, 255);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1.5, 0, 3);
	glScalef(0.5, 1.5, 0.5);
	glColor4ub(59, 59, 59, 255);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 0, 3.5);
	glScaled(5, -3, 0);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);

	glPopMatrix();

	//	تفاصيل الطابعة

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
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();

	glTranslated(-21, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 9.5);
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(130, 130, 130, 255);
	glutSolidCube(200);

	glPopMatrix();

	glPushMatrix();
	glTranslated(137, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37, 19.5, -100);
	glRotated(90, 0, 1, 0);
	glScalef(0, 5, 22.2);
	glColor4ub(125, 156, 159, 255);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-63, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(13.33);
	glPopMatrix();

	/// سقف
	glPushMatrix();
	glTranslated(37, 41, 0);
	glScalef(1, 0, 1);
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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


	glColor4ub(59, 59, 59, 255);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1.5, 0, 3);
	glScalef(0.5, 1.5, 0.5);
	glColor4ub(59, 59, 59, 255);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 0, 3.5);
	glScaled(5, -3, 0);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);

	glPopMatrix();

	//	تفاصيل الطابعة

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
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();

	glTranslated(-21, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 9.5);
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(130, 130, 130, 255);
	glutSolidCube(200);

	glPopMatrix();

	glPushMatrix();
	glTranslated(137, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37, 19.5, -100);
	glRotated(90, 0, 1, 0);
	glScalef(0, 5, 22.2);
	glColor4ub(125, 156, 159, 255);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-63, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(13.33);
	glPopMatrix();

	/// سقف
	glPushMatrix();
	glTranslated(37, 41, 0);
	glScalef(1, 0, 1);
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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


	glColor4ub(59, 59, 59, 255);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1.5, 0, 3);
	glScalef(0.5, 1.5, 0.5);
	glColor4ub(59, 59, 59, 255);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 0, 3.5);
	glScaled(5, -3, 0);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);

	glPopMatrix();

	//	تفاصيل الطابعة

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
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();

	glTranslated(-21, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 9.5);
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(130, 130, 130, 255);
	glutSolidCube(200);

	glPopMatrix();

	glPushMatrix();
	glTranslated(137, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37, 19.5, -100);
	glRotated(90, 0, 1, 0);
	glScalef(0, 5, 22.2);
	glColor4ub(125, 156, 159, 255);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-63, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(13.33);
	glPopMatrix();

	/// سقف
	glPushMatrix();
	glTranslated(37, 41, 0);
	glScalef(1, 0, 1);
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(105, 105, 105, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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


	glColor4ub(59, 59, 59, 255);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1.5, 0, 3);
	glScalef(0.5, 1.5, 0.5);
	glColor4ub(59, 59, 59, 255);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 0, 3.5);
	glScaled(5, -3, 0);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);

	glPopMatrix();

	//	تفاصيل الطابعة

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
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();

	glTranslated(-21, -150, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 9.5);
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(130, 130, 130, 255);
	glutSolidCube(200);

	glPopMatrix();

	glPushMatrix();
	glTranslated(107, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37.2, 19.4, -100);
	glRotated(90, 0, 1, 0);
	glScalef(0, 5, 15.6);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-33, 19.2, 0);
	glScalef(0, 3.35, 15);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(13.33);
	glPopMatrix();

	glPushMatrix();

	glTranslated(37, 41, 0);
	glScalef(0.7, 0, 1);
	glColor4ub(245, 241, 185, 255);
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
	glColor4ub(40, 7, 7, 255);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor4ub(40, 7, 7, 255);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor4ub(40, 7, 7, 255);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//; كرسي الضيوف

	glPushMatrix();

	glTranslated(0, -37, 0);

	glPushMatrix();

	glTranslated(4, 15, -10);
	glScalef(2, 2, 1.2);
	glColor4ub(28, 18, 18, 255);
	glutSolidCube(6);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1, 15, -2.5);
	glScalef(0.5, 2.5, 1.5);
	glColor4ub(28, 18, 18, 255);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(4.6, 20, -6.3);
	glScalef(1.3, 0.5, 0.8);
	glColor4ub(78, 62, 62, 255);
	gluCylinder(a, 4, 4, 3.5, 30, 30);

	glPopMatrix();

	glPushMatrix();

	glTranslated(4.6, 9, -6.3);
	glScalef(1.3, 0.5, 0.8);
	glColor4ub(78, 62, 62, 255);
	gluCylinder(a, 4, 4, 3.5, 30, 30);

	glPopMatrix();

	glPopMatrix();

	// كرسي الضيوف التاني

	glPushMatrix();

	glTranslated(60, -37, 0);

	glPushMatrix();

	glTranslated(-4, 15, -10);
	glScalef(2, 2, 1.2);
	glColor4ub(28, 18, 18, 255);
	glutSolidCube(6);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 15, -2.5);
	glScalef(0.5, 2.5, 1.5);
	glColor4ub(28, 18, 18, 255);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-4.6, 20, -6.3);
	glScalef(1.3, 0.5, 0.8);
	glColor4ub(78, 62, 62, 255);
	gluCylinder(a, 4, 4, 3.5, 30, 30);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-4.6, 9, -6.3);
	glScalef(1.3, 0.5, 0.8);
	glColor4ub(78, 62, 62, 255);
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

	glColor4ub(20, 20, 15, 255);
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

	glColor4ub(100, 100, 100, 255);
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

	glColor4ub(20, 20, 15, 255);
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
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();

	glTranslated(-5, -148, 7);
	glRotated(90, 0, 1, 0);
	glScalef(5, 0, 6.3);
	glColor4ub(245, 241, 185, 255);
	glutSolidCube(9);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	*/
	/*
	// fist staircase
	glColor4ub(245, 241, 185, 255);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glCallList(36);
	glPopMatrix();
	///////////////

	glCallList(35);
	*/

	drawDoctorRoom();

	printFPS();
	glutSwapBuffers();
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Use single display buffer.
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("hospital");
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