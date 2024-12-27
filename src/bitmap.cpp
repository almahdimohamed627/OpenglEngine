#include "bitmap.h"
#include <GL/glut.h> // Ensure GLUT is included for OpenGL functions

// Define the function
void renderBitmapText(float x, float y, const char *text, void *font)
{
    glRasterPos2f(x, y); // Set the position for the text
    for (const char *c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c); // Render each character
    }
}
