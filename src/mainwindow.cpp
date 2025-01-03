#include "globals.h"
#include <GL/freeglut.h>
#include <string>
#include <math.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <limits> // For std::numeric_limits
#include "bitmap.h"
#include "Entity.h"
#include "Shape.h"
#include "List.h"
#include "Sphere.h"
#include "Cube.h"
#include "Button.h"
#include "Transformation.h"
#include <exception>

std::vector<Entity *> entities;
Button sphere_button("Sphere", 20, 800 - 40);
Button cube_button("Cube", 20, 800 - 80);
Button teaPot_button("Tea Pot", 20, 800 - 120);

Button newList_button("New List", 20, 100);
Button lists_button("Lists", 20, 60);

template <typename T>
void input(T &value)
{
	if constexpr (std::is_same<T, std::string>::value) {
        std::getline(std::cin, value); // Read the whole line (including spaces)
		return;
    }
	while (!(std::cin >> value))
	{
		std::cout << "Invalid input. Please try again: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

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

		if (sphere_button.testCollision())
		{
			if (modeList)
			{
				dynamic_cast<List*>(entities[ListID])->pushEntity(new Sphere(ListID));
			}
			else
			{
				entities.push_back(new Sphere());
			}
		}
		else if (teaPot_button.testCollision())
		{
			if (modeList)
			{
				dynamic_cast<List*>(entities[ListID])->pushEntity(new Entity(ListID));
			}
			else
			{
				entities.push_back(new Entity());
			}
		}
		else if (cube_button.testCollision())
		{
			if (modeList)
			{
				dynamic_cast<List*>(entities[ListID])->pushEntity(new Cube(ListID));
			}
			else
			{
				entities.push_back(new Cube());
			}
		}
		else if (newList_button.testCollision())
		{
			std::cout << "Enter New List Name: " << std::flush;
			std::string listName;
			input(listName);
			entities.push_back(new List(listName));
			ListID = entities.back()->getId();
			modeList = true;
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
	if (Transformation::get() != '_')
	{
		if (direction > 0) // Scroll up
		{

			!entities.empty() ? entities[Shape::selected()]->transform(Transformation::get(), Transformation::getX(), Transformation::getY(), Transformation::getZ(), +1) : donothing();
		}
		else if (direction < 0) // Scroll down
		{
			!entities.empty() ? entities[Shape::selected()]->transform(Transformation::get(), Transformation::getX(), Transformation::getY(), Transformation::getZ(), -1) : donothing();
		}
	}
	else
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
	}
	// Update the scene
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: /* Escape key */
		Transformation::reset();
		break;
	case 'R':
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
		Transformation::reset();
		Shape::selected(1);
		break;
	case ',':
		Transformation::reset();
		Shape::selected(-1);
		break;
	case 'c':
		if (!entities.empty() && entities[Entity::selected()]->getType() == "Shape")
		{
			double r, g, b, a;
			std::cout << "Enter new color:" << std::endl;
			std::cout << "red: " << std::flush;
			input(r);
			std::cout << "green: " << std::flush;
			input(g);
			std::cout << "blue: " << std::flush;
			input(b);
			std::cout << "alpha: " << std::flush;
			input(a);
			dynamic_cast<Shape *>(entities[Entity::selected()])->setColor(r, g, b, a);
			std::cout << "Color updated to R=" << r << ", G=" << g << ", B=" << b << ", A=" << a << std::endl;
			std::cout << "done." << std::endl;
		}
		else
		{
			std::cout << "there is no entities or the selected entity is a list not a shape.." << std::endl;
		}
		break;
	case 3: // CTRL + C
		!entities.empty() ? entities.push_back(new Entity(entities[Entity::selected()])) : donothing();
		break;
	case 127: // DELETE
		if (!entities.empty())
		{
			delete entities[Shape::selected()];
			entities.erase(entities.begin() + Shape::selected());
			Shape::selected(-1);
		}
		break;
	case 't':
		Transformation::set('t');
		break;
	case 'r':
		Transformation::set('r');
		break;
	case 'e':
		Transformation::set('s');
		break;
	case 'x':
		Transformation::toggleX();
		break;
	case 'y':
		Transformation::toggleY();
		break;
	case 'z':
		Transformation::toggleZ();
		break;
	case 'q':
		Transformation::xyz();
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
		/*
	case GLUT_KEY_CTRL_L:
		ctrl_down =true;
		break;
		*/
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

	glutSpecialFunc(Special);
	glutKeyboardFunc(keyboard);

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