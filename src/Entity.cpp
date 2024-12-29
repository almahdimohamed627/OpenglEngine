#include "Entity.h"
#include <typeinfo>
#include <cstdio>
#include "bitmap.h"

int Entity::count = 0; // Definition of static variable
int Entity::selectedIndex = 0;

Entity::Entity()
    : translate_x(Ex), translate_y(E), translate_z(Ez),
      rotate_x(0), rotate_y(0), rotate_z(0),
      scale_x(1), scale_y(1), scale_z(1),
      red(0), green(0), blue(0), alpha(255)
{
    selectedIndex = count;
    id = count;
    count += 1;
}

Entity::Entity(Entity *e)
    : translate_x(e->translate_x), translate_y(e->translate_y), translate_z(e->translate_z),
      rotate_x(e->rotate_x), rotate_y(e->rotate_y), rotate_z(e->rotate_z),
      scale_x(e->scale_x), scale_y(e->scale_y), scale_z(e->scale_z),
      red(e->red), green(e->green), blue(e->blue), alpha(e->alpha)
{
    selectedIndex = count;
    id = count;
    count += 1;
}

Entity::~Entity()
{
    count--;
}

void Entity::applyTransformation()
{
    glColor4ub(red, green, blue, alpha);
    if (selectedIndex == id)
    {
        glColor4ub(255, 0, 0, 150);
    }
    glTranslated(translate_x, translate_y, translate_z);
    glRotated(rotate_x, 1, 0, 0);
    glRotated(rotate_y, 0, 1, 0);
    glRotated(rotate_z, 0, 0, 1);
    glScaled(scale_x, scale_y, scale_z);
}

void Entity::display()
{
    glPushMatrix();
    applyTransformation();
    glutSolidTeapot(2);
    glPopMatrix();
}

void Entity::displayInfo()
{
    char buffer[100];                      // Allocate a buffer for the formatted string
    sprintf(buffer, "name:: %s", "hello"); // Format the string
    renderBitmapText(0.8, -0.7, buffer, GLUT_BITMAP_HELVETICA_18);
}

int Entity::selected()
{
    return selectedIndex;
}
int Entity::selected(int index)
{
    selectedIndex += index;
    if (selectedIndex >= count)
    {
        selectedIndex = 0;
    }
    else if (selectedIndex < 0)
    {
        selectedIndex = count - 1;
    }
    return selectedIndex;
}

void Entity::setColor(int red, int green, int blue, int alpha)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}

void Entity::transform(char transformation, bool x, bool y, bool z, int amount)
{
    switch (transformation)
    {
    case 't':
        if (x)
        {
            translate_x += amount * 0.1;
        }
        if (y)
        {
            translate_y += amount * 0.1;
        }
        if (z)
        {
            translate_z += amount * 0.1;
        }
        break;
    case 'r':
        if (x)
        {
            rotate_x += amount;
        }
        if (y)
        {
            rotate_y += amount;
        }
        if (z)
        {
            rotate_z += amount;
        }
        break;
    case 's':
        if (x)
        {
            scale_x += amount * 0.1;
        }
        if (y)
        {
            scale_y += amount * 0.1;
        }
        if (z)
        {
            scale_z += amount * 0.1;
        }
        break;

    default:
        break;
    }
}
