#include <cstdio>
#include "Transformation.h"
#include "bitmap.h"

char Transformation::applaid = '_';
bool Transformation::onX = false;
bool Transformation::onY = false;
bool Transformation::onZ = false;

void Transformation::display()
{
    char buffer[10];                                                                             // Allocate a buffer for the formatted string
    sprintf(buffer, "%c    %c%c%c", applaid, onX ? 'x' : '_', onY ? 'y' : '_', onZ ? 'z' : '_'); // Format the string
    renderBitmapText(0.2, 0.95, buffer, GLUT_BITMAP_HELVETICA_18);
}

void Transformation::reset()
{
    applaid = '_';
    onX = false;
    onY = false;
    onZ = false;
}

void Transformation::toggleX()
{
    if (onX)
    {
        onX = false;
    }
    else
    {
        onX = true;
    }
}
void Transformation::toggleY()
{
    if (onY)
    {
        onY = false;
    }
    else
    {
        onY = true;
    }
}
void Transformation::toggleZ()
{
    if (onZ)
    {
        onZ = false;
    }
    else
    {
        onZ = true;
    }
}

void Transformation::xyz()
{
    onX = true;
    onY = true;
    onZ = true;
}

void Transformation::set(char transformation)
{
    applaid = transformation;
}

char Transformation::get()
{
    return applaid;
}

bool Transformation::getX()
{
    return onX;
}

bool Transformation::getY()
{
    return onY;
}

bool Transformation::getZ()
{
    return onZ;
}

