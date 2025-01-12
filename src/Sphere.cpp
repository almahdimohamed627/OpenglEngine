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


std::string Sphere::getDisplayCode() {
    char buffer[100];
    std::string temp = "";
    temp +="glPushMatrix();\n";
    sprintf(buffer, "glColor4ub(%.2f, %.2f, %.2f, %.2f);\n", red, green, blue, alpha);
    temp+=buffer;
    sprintf(buffer, "glTranslated(%.2f, %.2f, %.2f);\n", translate_x, translate_y, translate_z);
    temp+=buffer;
    sprintf(buffer, "glRotated(%.2f, 1, 0, 0);\n", rotate_x);
    temp+=buffer;
    sprintf(buffer, "glRotated(%.2f, 0, 1, 0);\n", rotate_y);
    temp+=buffer;
    sprintf(buffer, "glRotated(%.2f, 0, 0, 1);\n", rotate_z);
    temp+=buffer;
    sprintf(buffer, "glScaled(%.2f, %.2f, %.2f);\n", scale_x, scale_y, scale_z);
    temp+=buffer;
    temp +="glutSolidSphere(1, 50, 50);  // Sphere\n";
    temp +="glPopMatrix();\n";
    return temp;
}


