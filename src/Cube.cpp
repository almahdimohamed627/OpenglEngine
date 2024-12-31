#include "Cube.h"

Cube::Cube() : Shape()
{
    name ="Cube";
}
void Cube::display()
{
    glPushMatrix();
    applyTransformation();
    glutSolidCube(1);
    glPopMatrix();
}
