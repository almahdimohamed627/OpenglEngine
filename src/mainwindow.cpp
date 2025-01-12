#include "globals.h"
#include <GL/freeglut.h>
#include <string>
#include <math.h>
#include <iostream>
#include <cstdio>
#include "MyVector.h"
#include <limits> // For std::numeric_limits
#include "bitmap.h"
#include "Entity.h"
#include "Shape.h"
#include "List.h"
#include "Sphere.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Button.h"
#include "Transformation.h"
#include "FileHandler.h"
#include <exception>
MyVector entities;
#include "getCode.h"
#include <filesystem>			// Ensure this header is included
namespace fs = std::filesystem; // Define the alias

Button sphere_button("Sphere", 20, 800 - 40);
Button cube_button("Cube", 20, 800 - 80);
Button teaPot_button("Tea Pot", 20, 800 - 120);
Button cylinder_button("Cylinder", 20, 800 - 160);

Button newList_button("New List", 20, 180);
Button lists_button("Lists", 20, 140);
Button editList_button("Edit List", 20, 100);
Button saveList_button("Save List", 20, 60);
Button saveToCode_button("Save To Code ", 20, 20);
std::vector<Button *> lists_buttons;

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

		if (lists_button.testCollision())
		{
			if (showingLists)
				showingLists = false;
			else
				showingLists = true;
		}
		else if (showingLists)
		{
			for (Button *list : lists_buttons)
			{
				if (list->testCollision())
				{
					char fileName[100];
					sprintf(fileName, "Lists/%s.json", list->getName().c_str());
					// Load JSON from a file
					std::ifstream file(fileName);
					json j;
					file >> j;

					// Deserialize into a List object
					entities += new List(list->getName());
					entities[Entity::selected()]->fromJSON(j);
					showingLists = false;
				}
			}
		}
		else if (sphere_button.testCollision())
		{
			if (modeList)
			{
				dynamic_cast<List *>(entities[ListID])->pushEntity(new Sphere(entities[ListID], Ex, E, Ez));
			}
			else
			{
				entities += new Sphere(Ex, E, Ez);
			}
		}
		else if (teaPot_button.testCollision())
		{
			if (modeList)
			{
				// dynamic_cast<List *>(entities[ListID])->pushEntity(new Entity(ListID));
			}
			else
			{
				// entities += new Entity();
			}
		}
		else if (cube_button.testCollision())
		{
			if (modeList)
			{
				dynamic_cast<List *>(entities[ListID])->pushEntity(new Cube(entities[ListID], Ex, E, Ez));
			}
			else
			{
				entities += new Cube(Ex, E, Ez);
			}
		}
		else if (cylinder_button.testCollision())
		{
			if (modeList)
			{
				dynamic_cast<List *>(entities[ListID])->pushEntity(new Cylinder(entities[ListID], Ex, E, Ez));
			}
			else
			{
				entities += new Cylinder(Ex, E, Ez);
			}
		}
		else if (newList_button.testCollision())
		{
			std::cout << "Enter New List Name: " << std::flush;
			std::string listName;
			input(listName);
			entities += new List(listName);
			ListID = entities.back()->getId();
			modeList = true;
		}
		else if (saveList_button.testCollision() && modeList)
		{
			// Save the JSON to a file
			try
			{
				char buffer[100];
				sprintf(buffer, "Lists/%s.json", entities[ListID]->getName().c_str());
				FileHandler::writeToFile(buffer, entities[ListID]->toJSON().dump(4)); // Save with pretty formatting
				std::cout << "List saved to " << buffer << " successfully." << std::endl;
				Entity::selected(ListID);
				modeList = false;
			}
			catch (const std::exception &e)
			{
				std::cerr << "Error saving file: " << e.what() << std::endl;
			}
		}

		else if (editList_button.testCollision())
		{
			ListID = entities[Entity::selected()]->getId();
			modeList = true;
		}
		else if (saveToCode_button.testCollision())
		{
			getCode();
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
			if (modeList)
			{
				dynamic_cast<List *>(entities[ListID])->m_entities[Entity::selected()]->transform(Transformation::get(), Transformation::getX(), Transformation::getY(), Transformation::getZ(), +1);
			}
			else
			{
				!entities.empty() ? entities[Entity::selected()]->transform(Transformation::get(), Transformation::getX(), Transformation::getY(), Transformation::getZ(), +1) : donothing();
			}
		}
		else if (direction < 0) // Scroll down
		{
			if (modeList)
			{
				dynamic_cast<List *>(entities[ListID])->m_entities[Entity::selected()]->transform(Transformation::get(), Transformation::getX(), Transformation::getY(), Transformation::getZ(), -1);
			}
			else
			{
				!entities.empty() ? entities[Entity::selected()]->transform(Transformation::get(), Transformation::getX(), Transformation::getY(), Transformation::getZ(), -1) : donothing();
			}
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
		// printf("Mouse wheel scrolled. E = %.2f\n", E);
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
		if (modeList)
		{
			Entity::selected(dynamic_cast<List *>(entities[ListID])->m_entities.next(Entity::selected()));
		}
		else
		{
			Entity::selected(entities.next(Entity::selected()));
		}
		break;
	case ',':
		Transformation::reset();
		if (modeList)
		{
			Entity::selected(dynamic_cast<List *>(entities[ListID])->m_entities.prev(Entity::selected()));
		}
		else
		{
			Entity::selected(entities.prev(Entity::selected()));
		}
		break;
	case 'c':
		if (entities.empty())
			break;
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
		if (modeList)
		{
			dynamic_cast<Shape *>(dynamic_cast<List *>(entities[ListID])->m_entities[Entity::selected()])->setColor(r, g, b, a);
		}
		else
		{
			dynamic_cast<Shape *>(entities[Entity::selected()])->setColor(r, g, b, a);
		}
		std::cout << "Color updated to R=" << r << ", G=" << g << ", B=" << b << ", A=" << a << std::endl;
		std::cout << "done." << std::endl;

		break;
	case 3: // CTRL + C
		if (modeList)
		{
			dynamic_cast<List *>(entities[ListID])->pushEntity(dynamic_cast<List *>(entities[ListID])->m_entities[Entity::selected()]->clone());
		}
		else
		{
			!entities.empty() ? entities += entities[Entity::selected()]->clone() : donothing();
		}

		break;
	case 127: // DELETE
		if (modeList)
		{
			delete dynamic_cast<List *>(entities[ListID])->m_entities[Entity::selected()];
			dynamic_cast<List *>(entities[ListID])->m_entities.erase(Entity::selected());
			Entity::selected(dynamic_cast<List *>(entities[ListID])->m_entities.next(Entity::selected()));
		}
		else
		{
			if (!entities.empty())
			{
				delete entities[Entity::selected()];
				entities.erase(Entity::selected());
				Entity::selected(entities.next(Entity::selected()));
			}
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

	try
	{
		// Iterate through the directory
		int counter = 0;
		for (const auto &entry : fs::directory_iterator("./Lists/"))
		{
			if (entry.is_regular_file())
			{ // Check if it's a file
				lists_buttons.push_back(new Button(entry.path().stem().string(), (counter/20)*160 + 200, 765 - (counter%20) * 40));
			}
			counter++;
		}
	}
	catch (const fs::filesystem_error &e)
	{
		std::cerr << "Error: " << e.what() << "\n";
	}

	Timer(0);
	glutDisplayFunc(DrawGLScene);
	setupprojection();
	glutMainLoop();
	return 0;
}