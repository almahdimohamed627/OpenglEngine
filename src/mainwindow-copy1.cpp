#include <GL/glut.h>
#include <cstdio> // For printf
#include <string>
#include <iostream>

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
	bool testCollision()
	{
		std::cout << x + 20 + (this->text.length() * 9.0) << " || " << x << std::endl;
		if (mouseX > this->x)
		{
			printf("He touched me owo\n");
		}
		return true;
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
Button test("test", 20, 20);
Button hello("hello my name is mohamed", 20, 60);

// Variables to store the current mouse position

// Callback for mouse button clicks
void mouseButton(int button, int state, int x, int y)
{
	// Check which button is clicked
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("Left button pressed at (%d, %d)\n", x, y);
		mouseX = x;
		mouseY = y;
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
	//printf("Mouse moved to (%d, %d) without pressing any button\n", x, y);
}

// OpenGL display function
void display()
{
	hello.testCollision();
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw the background grid
	glPushMatrix();
	for (int i = 0; i <= 30; i++)
	{
		glColor3f(0.7f, 0.7f, 0.7f); // Set the line color to gray
		glLineWidth(2.0f);			 // Set the line width (optional)
		glBegin(GL_LINES);			 // Begin drawing lines
		// First segment: from top-middle to middle
		glVertex2f(-1.0f, 1.0f);  // Top-middle
		glVertex2f(-1.0f, -1.0f); // Bottom-middle
		glEnd();
		glTranslated(2 / 30.0f, 0, 0);
	}
	glPopMatrix();

	glPushMatrix();
	for (int i = 0; i <= 20; i++)
	{
		glColor3f(0.7f, 0.7f, 0.7f); // Set the line color to gray
		glLineWidth(2.0f);			 // Set the line width (optional)
		glBegin(GL_LINES);			 // Begin drawing lines
		// First segment: from top-middle to middle
		glVertex2f(-1.0f, -1.0f); // Top-middle
		glVertex2f(1.0f, -1.0f);  // Bottom-middle
		glEnd();
		glTranslated(0, 2 / 20.0f, 0);
	}
	glPopMatrix();

	/////

	glPushMatrix();
	// Draw the center red point
	glColor3f(1.0f, 0.0f, 0.0f); // Red color
	glPointSize(10.0f);			 // Large point
	glBegin(GL_POINTS);
	glVertex2f(0, 0); // Transform coordinates
	glEnd();
	glPopMatrix();

	// Draw toolBox
	// Draw the filled square (gray color)
	glColor3f(0.5f, 0.5f, 0.5f); // Set color to gray (R=0.5, G=0.5, B=0.5)
	glBegin(GL_QUADS);			 // Start drawing a filled quadrilateral
	glVertex2f(-1.0f, -1.0f);	 // Bottom-left corner
	glVertex2f(-0.8f, -1.0f);	 // Bottom-right corner
	glVertex2f(-0.8f, 1.0f);	 // Top-right corner
	glVertex2f(-1.0f, 1.0f);	 // Top-left corner
	glEnd();

	// Draw the border (black color)
	glColor3f(0.0f, 0.0f, 0.0f); // Set color to black
	glLineWidth(3.0f);			 // Set line thickness
	glBegin(GL_LINE_LOOP);		 // Start drawing a looped line
	glVertex2f(-1.0f, -1.0f);	 // Bottom-left corner
	glVertex2f(-0.8f, -1.0f);	 // Bottom-right corner
	glVertex2f(-0.8f, 1.0f);	 // Top-right corner
	glVertex2f(-1.0f, 1.0f);	 // Top-left corner
	glEnd();
	test.display();
	hello.display();
	glFlush();
}

// Main function
int main(int argc, char **argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1500, 900);
	glutCreateWindow("GLUT Mouse Motion Example");

	// Set the background color to white
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Set the display function
	glutDisplayFunc(display);

	// Register mouse callbacks
	glutMouseFunc(mouseButton);				   // For mouse button presses
	glutMotionFunc(mouseMotion);			   // For mouse dragging (motion while holding a button)
	glutPassiveMotionFunc(passiveMouseMotion); // For motion without button presses

	// Enter the GLUT main loop
	glutMainLoop();
	return 0;
}
