#include <typeinfo>
#include <cstdio>
#include "Shape.h"
#include "bitmap.h"

Shape::Shape()
    : Entity(), red(0), green(0), blue(0), alpha(255)
{
    this->type = "Shape";
    this->name = "General";
}
Shape::Shape(int p_id) : Entity(p_id), red(0), green(0), blue(0), alpha(255)
{
    this->type = "Shape";
    this->name = "General";
}

Shape::Shape(Shape *e)
    : Entity(e), red(e->red), green(e->green), blue(e->blue), alpha(e->alpha)
{
}

void Shape::applyTransformation()
{
    glColor4ub(red, green, blue, alpha);
    Entity::applyTransformation();
}

void Shape::display()
{
    glPushMatrix();
    applyTransformation();
    glutSolidTeapot(2);
    glPopMatrix();
}

void Shape::setColor(int red, int green, int blue, int alpha)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}

void Shape::displayInfo()
{
    char buffer[1000];                                                                                                                                                                                                                                                                                                                       // Allocate a buffer for the formatted string
    sprintf(buffer, "type: %s | name: %s | x:%.2f y:%.2f z:%.2f | rotation: x:%.2f y:%.2f z:%.2f | scale: x:%.2f y:%.2f z:%.2f | color: R:%.2f G:%.2f B:%.2f Alpha:%.2f ", this->type.c_str(), this->name.c_str(), translate_x, translate_y, translate_z, rotate_x, rotate_y, rotate_z, scale_x, scale_y, scale_z, red, green, blue, alpha); // Format the string
    renderBitmapText(-0.75, -0.98, buffer, GLUT_BITMAP_HELVETICA_18);
}