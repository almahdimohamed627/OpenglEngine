#include "Sphere.h"

void Sphere::display() {
    glPushMatrix();
    applyTransformation();
    glutSolidSphere(1, 50, 50);
    glPopMatrix();
}
