#include "Sphere.h"

Sphere::Sphere() : Shape()
{
    name = "Sphere";
}

Sphere::Sphere(double x, double y, double z) : Shape(x, y, z)
{
    name = "Sphere";
}

Sphere::Sphere(Entity *p_perant, double x, double y, double z) : Shape(p_perant, x, y, z)
{
    name = "Sphere";
}
Sphere::Sphere(Sphere *e) : Shape(e) {}

void Sphere::display()
{
    glPushMatrix();
    applyTransformation();
    glutSolidSphere(1, 50, 50);
    glPopMatrix();
}

Sphere *Sphere::clone()
{
    return new Sphere(this);
}
