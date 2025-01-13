#include "globals.h"
#include "Cylinder.h"

Cylinder::Cylinder() : Shape()
{
    name = "Cylinder";
}

Cylinder::Cylinder(double x, double y, double z) : Shape(x, y, z)
{
    name = "Cylinder";
}

Cylinder::Cylinder(Entity *p_perant, double x, double y, double z) : Shape(p_perant, x, y, z)
{
    name = "Cylinder";
}
Cylinder::Cylinder(Cylinder *e) : Shape(e) {}

void Cylinder::display()
{
    glPushMatrix();
    applyTransformation();
   // Draw the cylinder sides
    gluCylinder(a, 1.0, 1.0, 1.0, 50, 50);

    // Draw the bottom cap
    glPushMatrix();
    glRotatef(180, 1.0f, 0.0f, 0.0f); // Flip to face downwards
    gluDisk(a, 0.0, 1.0, 50, 50);   // Draw the bottom disk
    glPopMatrix();

    // Draw the top cap
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f); // Move to the top of the cylinder
    gluDisk(a, 0.0, 1.0, 50, 50); // Draw the top disk
    glPopMatrix();
    glPopMatrix();
}

Cylinder *Cylinder::clone()
{
    return new Cylinder(this);
}


std::string Cylinder::getDisplayCode() {
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
    temp +="gluCylinder(a, 1.0, 1.0, 1.0, 50, 50);  // Cylinder\n";
    temp+= "glPushMatrix();\n";
    temp+= "glRotatef(180, 1.0f, 0.0f, 0.0f);\n";
    temp+= "gluDisk(a, 0.0, 1.0, 50, 50);  // buttom disk\n";
    temp+= "glPopMatrix();\n";
    temp+= "glPushMatrix();\n";
    temp+= "glTranslatef(0.0f, 0.0f, 1.0f);\n";
    temp+= "gluDisk(a, 0.0, 1.0, 50, 50);   // top disk\n";
    temp+= "glPopMatrix();\n";
    temp +="glPopMatrix();\n";
    return temp;
}


