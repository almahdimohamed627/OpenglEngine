#include "globals.h"
#include <GL/freeglut.h>
#include <string>
#include <math.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include "bitmap.h"
#include "Entity.h"
#include "Sphere.h"
#include "Cube.h"
#include "Button.h"

std::vector<Entity *> entities;
Button Sphere_button("Sphere", 20, 20);
Button Cube_button("Cube", 20, 60);
Button TeaPot_button("Tea Pot", 20, 100);
// Callback for mouse button clicks
void mouseButton(int button, int state, int x, int y)
{
	// Check which button is clicked
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// printf("Left button pressed at (%d, %d)\n", x, y);
		mouseX = x;
		mouseY = y;
		mouseTh = th;

		if (Sphere_button.testCollision())
		{
			entities.push_back(new Sphere());
		}
		else if (TeaPot_button.testCollision())
		{
			entities.push_back(new Entity());
		}
		else if (Cube_button.testCollision())
		{
			entities.push_back(new Cube());
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		printf("Right button pressed at (%d, %d)\n", x, y);
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		printf("Middle button pressed at (%d, %d)\n", x, y);
	}

	// Store the position of the mouse when a button is pressed
}

// Callback for mouse motion while holding a button
void mouseMotion(int x, int y)
{
	// printf("Mouse dragged to (%d, %d)\n", x, y);
	th = (x - mouseX) / 360.0 + mouseTh;
}

// Callback for mouse motion without holding a button
void passiveMouseMotion(int x, int y)
{
	// printf("Mouse moved to (%d, %d) without pressing any button\n", x, y);
}

// Mouse wheel callback function
void mouseWheel(int wheel, int direction, int x, int y)
{
	if (direction > 0) // Scroll up
	{
		E += 1.0; // Move "up" along the y-axis or zoom in
	}
	else if (direction < 0) // Scroll down
	{
		E -= 1.0; // Move "down" along the y-axis or zoom out
	}

	// Print the new E value (optional)
	printf("Mouse wheel scrolled. E = %.2f\n", E);

	// Update the scene
	glutPostRedisplay();
}

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
	case 'd':
		if (sprinting)
		{
			Ex = Ex - 5 * sin(th);
			Ez = Ez + 5 * cos(th);
		}
		else
		{
			Ex = Ex - 2 * sin(th);
			Ez = Ez + 2 * cos(th);
		}
		break;
	case 'a':
		if (sprinting)
		{
			Ex = Ex + 5 * sin(th);
			Ez = Ez - 5 * cos(th);
		}
		else
		{
			Ex = Ex + 2 * sin(th);
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
	case '.':
		Entity::selected(1);
		break;
	case ',':
		Entity::selected(-1);
		break;
	case 'c':
		int r, g, b, a;
		std::cout << "Enter new color:" << std::endl;
		std::cout << "red: " << std::flush;
		std::cin >> r;
		std::cout << "green: " << std::flush;
		std::cin >> g;
		std::cout << "blue: " << std::flush;
		std::cin >> b;
		std::cout << "alpha: " << std::flush;
		std::cin >> a;
		entities[Entity::selected()]->setColor(r, g, b, a);
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
	glPushMatrix();
	timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	char buffer[100];															 // Allocate a buffer for the formatted string
	sprintf(buffer, "FPS:%d X:%.2f Y:%.2f Z:%.2f", 1000 / deltaTime, Ex, E, Ez); // Format the string
	renderBitmapText(0.5, 0.95, buffer, GLUT_BITMAP_HELVETICA_18);				 // Pass the formatted string																				 // std::cout << '\r' << 1000 / deltaTime << " " << Ex << " " << E << " " << Ez << std::flush;
	glPopMatrix();
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

#include "displayfunc.h"

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
	glutInitWindowSize(1500, 800);
	glutCreateWindow("stadium");
	InitGL();
	glutReshapeFunc(ReSizeGLScene);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(Special);

	// Register mouse callbacks
	glutMouseFunc(mouseButton);				   // For mouse button presses
	glutMotionFunc(mouseMotion);			   // For mouse dragging (motion while holding a button)
	glutPassiveMotionFunc(passiveMouseMotion); // For motion without button presses
	glutMouseWheelFunc(mouseWheel);

	Timer(0);
	glutDisplayFunc(DrawGLScene);
	setupprojection();
	glutMainLoop();
	return 0;
}