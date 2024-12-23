#include <GL/glut.h>
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
bool sprinting = false;
bool light = false;
bool lighting = false;
bool rotateScene = false;
bool OpDoorOpen = false;
bool doorOpen = false;
double roofT = 0;
bool roof = false;
double pos = 0.0;

double ads[50];
double sideAds[50];
const char *adFile[50];
GLuint adTexture[50];
GLuint manchester_cityTexture;
GLuint cameraTexture;

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
		if (rotateScene)
			rotateScene = false;
		else
			rotateScene = true;
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
		if (OpDoorOpen)
		{
			OpDoorOpen = false;
		}
		else
		{
			OpDoorOpen = true;
		}
		break;
	case 'c':
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
		if (roof)
		{
			roof = false;
		}
		else
		{
			roof = true;
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
void initYelloBlock()
{
	glPushMatrix();
	glNewList(5, GL_COMPILE);
	glPushMatrix();
	glColor4ub(0, 30, 72, 255);
	glBegin(GL_QUADS);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 6, 0);
	glVertex3d(0, 6, 7);
	glVertex3d(0, 0, 7);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	for (int i = 0; i < 10; i++)
	{

		glPushMatrix();
		glColor4ub(0, 30, 72, 255);
		glBegin(GL_QUADS);
		glVertex3d(0, 6, 0);
		glVertex3d(0.7, 6, 0);
		glVertex3d(0.7, 6, 7);
		glVertex3d(0, 6, 7);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3d(0.7, 6, 0);
		glVertex3d(0.7, 6.35, 0);
		glVertex3d(0.7, 6.35, 7);
		glVertex3d(0.7, 6, 7);
		glEnd();
		glPopMatrix();
		//// الدرج
		glPushMatrix();
		glColor4ub(70, 70, 70, 255);
		glBegin(GL_QUADS);
		glVertex3d(0.3, 6.175, 0);
		glVertex3d(0.7, 6.175, 0);
		glVertex3d(0.7, 6.175, 1);
		glVertex3d(0.3, 6.175, 1);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3d(0.3, 6, 0);
		glVertex3d(0.3, 6.175, 0);
		glVertex3d(0.3, 6.175, 1);
		glVertex3d(0.3, 6, 1);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glTranslated(0.4, 6, 1.3);
		glColor4ub(194.9, 183.8, 0, 255);

		for (int i = 0; i < 10; i++)
		{
			glCallList(3);
			glTranslated(0, 0, 0.5);
		}
		glPopMatrix();
		glTranslated(0.7, 0.35, 0);
	}
	glPopMatrix();
	glEndList();
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

	glClearColor(0.546, 0.775, 0.925, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat position[] = {0, 10000, 0, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	gluLookAt(Ex, E + 1.7, Ez, Ex + cos(th), E + 1.7, Ez + sin(th), 0, 1, 0);
	GLUquadricObj *a = gluNewQuadric();
	if (rotateScene)
	{
		glRotated(90, 0, 0, 1);
	}

	
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
	glutCreateWindow("stadium");
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