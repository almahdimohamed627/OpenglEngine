#include "Cube.h"

Cube::Cube() : Shape()
{
    name ="Cube";
}

Cube::Cube(int p_id) : Shape(p_id)  {
    name ="Cube";
}

void Cube::display()
{
    glPushMatrix();
    applyTransformation();
    glutSolidCube(1);
    glPopMatrix();
}
