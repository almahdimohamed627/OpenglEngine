#include "Sphere.h"

Sphere::Sphere() : Shape()
{
    name = "Sphere";
}

Sphere::Sphere(int p_id) : Shape(p_id)
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
