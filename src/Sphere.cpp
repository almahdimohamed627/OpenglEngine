#include "Sphere.h"

Sphere::Sphere() : Shape()
{
    name = "Sphere";
}

void Sphere::display()
{
    glPushMatrix();
    applyTransformation();
    glutSolidSphere(1, 50, 50);
    glPopMatrix();
}
