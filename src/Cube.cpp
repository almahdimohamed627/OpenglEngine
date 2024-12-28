#include "Cube.h"

void Cube::display() {
    glPushMatrix();
    transform();
    glutSolidCube(1);
    glPopMatrix();
}
