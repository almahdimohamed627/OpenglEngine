#include "Sphere.h"

void Sphere::display() {
    glPushMatrix();
    transform();
    glutSolidSphere(1, 50, 50);
    glPopMatrix();
}
