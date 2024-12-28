#include "Cube.h"

void Cube::display() {
    glPushMatrix();
    applyTransformation();
    glutSolidCube(1);
    glPopMatrix();
}
