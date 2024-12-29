#include "Sphere.h"

Sphere::Sphere() : Entity()
{
    name = "Sphere";
}

void Sphere::display() {
    glPushMatrix();
    applyTransformation();
    glutSolidSphere(1, 50, 50);
    glPopMatrix();
}
