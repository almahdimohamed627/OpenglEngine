#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <cstdio> // For printf
#include <string>
#include <vector>

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
int mouseX = 0, mouseY = 0;
// Function to render bitmap text on the screen
void renderBitmapText(float x, float y, const char *text, void *font)
{
	glRasterPos2f(x, y); // Set the position for the text
	for (const char *c = text; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c); // Render each character
	}
}

class Circle
{
private: // Private members (default access specifier if omitted)
	int translate_x = Ex, translate_y = E, translate_z = Ez;
	int rotate_x = 0, rotate_y = 0, rotate_z = 0;
	int scale_x = 1, scale_y = 1, scale_z = 1;
	int red = 0, green = 0, blue = 0, alpha = 255;

public: // Public members
	// Constructor
	Circle()
	{
	}

	void display()
	{
		glPushMatrix();
		glColor4ub(red, green, blue, alpha);
		glTranslated(translate_x, translate_y, translate_z);
		glRotated(rotate_x, 1, 0, 0);
		glRotated(rotate_y, 0, 1, 0);
		glRotated(rotate_z, 0, 0, 1);
		glScaled(scale_x, scale_y, scale_z);
		glutSolidSphere(1, 50, 50);
		glPopMatrix();
	}
};

class Button
{
private:			  // Private members (default access specifier if omitted)
	std::string text; // Accessible only within the class
	double x, y;

public: // Public members
	// Constructor
	Button(std::string text, double x, double y)
	{
		this->text = text;
		this->x = x;
		this->y = y;
	}
	bool testCollision(void (*func)())
	{
		// Get the button's width
		float buttonWidth = 20 + (this->text.length() * 9.0);
		// Check if mouse is inside the button bounds
		if (mouseX >= this->x && mouseX <= (this->x + buttonWidth) &&
			mouseY >= this->y && -mouseY <= (this->y + 30))
		{
			func();
			return true;
		}
		return false;
	}

	void display()
	{
		// Draw the filled square blue
		glColor3ub(44.7, 93.1, 83.5);																// Set color to gray (R=0.5, G=0.5, B=0.5)
		glBegin(GL_QUADS);																			// Start drawing a filled quadrilateral
		glVertex2f((x - 750) / 750.0, (y - 400) / 400.0);											// Bottom-left corner
		glVertex2f((x + 20 + (this->text.length() * 9.0) - 750.0) / 750.0, (y - 400) / 400.0);		// Bottom-right corner
		glVertex2f((x + 20 + (this->text.length() * 9.0) - 750.0) / 750.0, (y + 30 - 400) / 400.0); // Top-right corner
		glVertex2f((x - 750) / 750.0f, (y + 30 - 400) / 400.0);										// Top-left corner
		glEnd();

		// Draw the border (black color)
		glColor3f(0.0f, 0.0f, 0.0f);																// Set color to black
		glLineWidth(3.0f);																			// Set line thickness
		glBegin(GL_LINE_LOOP);																		// Start drawing a looped line
		glVertex2f((x - 750) / 750.0, (y - 400) / 400.0);											// Bottom-left corner
		glVertex2f((x + 20 + (this->text.length() * 9.0) - 750.0) / 750.0, (y - 400) / 400.0);		// Bottom-right corner
		glVertex2f((x + 20 + (this->text.length() * 9.0) - 750.0) / 750.0, (y + 30 - 400) / 400.0); // Top-right corner
		glVertex2f((x - 750) / 750.0f, (y + 30 - 400) / 400.0);
		glEnd();

		renderBitmapText((x + 10 - 750) / 750.0, (y + 10 - 400) / 400.0, text.c_str(), GLUT_BITMAP_HELVETICA_18); // Large Helvetica
	}
};

std::vector<Circle *> circles;

Button circle_button("Circle", 20, 20);
Button hello("hello my name is mohamed", 20, 60);
// Callback for mouse button clicks
void mouseButton(int button, int state, int x, int y)
{
	// Check which button is clicked
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("Left button pressed at (%d, %d)\n", x, y);
		mouseX = x;
		mouseY = y;

		circle_button.testCollision(
			[]()
			{
				circles.push_back(new Circle());
			});
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
	printf("Mouse dragged to (%d, %d)\n", x, y);
}

// Callback for mouse motion without holding a button
void passiveMouseMotion(int x, int y)
{
	// printf("Mouse moved to (%d, %d) without pressing any button\n", x, y);
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
void DrawGLScene(void)
{
	glClearColor(1, 1, 1, 0.0f);						// Set background to white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear both color and depth buffers

	// --- 3D Rendering ---
	glMatrixMode(GL_MODELVIEW); // Ensure we're in the modelview matrix mode
	glLoadIdentity();			// Reset transformations

	GLfloat position[] = {0, 10000, 0, 0}; // Light position
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	gluLookAt(Ex, E, Ez, Ex + cos(th), E, Ez + sin(th), 0, 1, 0); // Camera setup

	if (rotateScene)
	{
		glRotated(90, 0, 0, 1); // Rotate the scene if needed
	}

	// Draw the background grid
	glPushMatrix();
	glColor3f(0.7f, 0.7f, 0.7f); // Set the line color to gray
	glLineWidth(1.0f);			 // Set the line width

	// Draw vertical grid lines
	for (int i = -150; i <= 150; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(i * 2.0f, 0.0f, -300.0f); // Line start
		glVertex3f(i * 2.0f, 0.0f, 300.0f);	 // Line end
		glEnd();
	}

	// Draw horizontal grid lines
	for (int i = -150; i <= 150; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(-300.0f, 0.0f, i * 2.0f); // Line start
		glVertex3f(300.0f, 0.0f, i * 2.0f);	 // Line end
		glEnd();
	}

	for (Circle *c : circles)
	{
		c->display();
	}

	glPopMatrix();
	// --- Switch to 2D for UI rendering ---
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Set orthographic projection (2D)

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST); // Disable depth testing for 2D UI rendering

	// Draw the center red point
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f); // Red color
	glPointSize(10.0f);			 // Large point
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f); // Transform coordinates
	glEnd();
	glPopMatrix();

	// Render 2D UI elements (buttons, labels, etc.)
	circle_button.display();
	hello.display();
	printFPS();		   // Print FPS
	glEnable(GL_DEPTH_TEST); // Re-enable depth testing for 3D rendering after UI

	glPopMatrix(); // Restore modelview matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); // Restore projection matrix
	glutSwapBuffers(); // Swap buffers to display the rendered content
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

	Timer(0);
	glutDisplayFunc(DrawGLScene);
	setupprojection();
	glutMainLoop();
	return 0;
}