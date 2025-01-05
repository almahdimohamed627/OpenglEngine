#include "Cube.h"

Cube::Cube() : Shape()
{
    name ="Cube";
}

Cube::Cube(double x, double y, double z) : Shape(x, y, z)
{
    name ="Cube";
}

Cube::Cube(Entity *p_perant, double x, double y, double z) : Shape(p_perant, x, y, z)  {
    name ="Cube";
}

Cube::Cube(Cube* e) : Shape(e) {}

void Cube::display()
{
    glPushMatrix();
    applyTransformation();
    glutSolidCube(1);
    glPopMatrix();
}

Cube* Cube::clone() {
    return new Cube(this);
}
