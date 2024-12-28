#include "Entity.h"

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

void Entity::setColor(int red, int green, int blue, int alpha) {
    this->red=red;
    this->green=green;
    this->blue=blue;
    this->alpha=alpha;
}

void Entity::transform(char transformation, bool x, bool y, bool z, int amount) {
    switch (transformation)
    {
    case 't':
        if(x) {
            translate_x+=amount;
        }
        if(y) {
            translate_y+=amount;
        }
        if(z) {
            translate_z+=amount;
        }
        break;
    case 'r':
        if(x) {
            rotate_x+=amount;
        }
        if(y) {
            rotate_y+=amount;
        }
        if(z) {
            rotate_z+=amount;
        }
        break;
    case 's':
        if(x) {
            scale_x+=amount*0.01;
        }
        if(y) {
            scale_y+=amount*0.1;
        }
        if(z) {
            scale_z+=amount*0.1;
        }
        break;
    
    default:
        break;
    }


}
