#include "Cube.h"

Cube::Cube() : Entity()
{
    name ="Cube";
}
void Cube::display() {
    glPushMatrix();
    applyTransformation();
    glutSolidCube(1);
    glPopMatrix();
}
