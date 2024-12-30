#include "Cube.h"

Cube::Cube() : Shape()
{
    type ="Cube";
}
void Cube::display()
{
    glPushMatrix();
    applyTransformation();
    glutSolidCube(1);
    glPopMatrix();
}
