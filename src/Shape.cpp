#include <typeinfo>
#include <cstdio>
#include "Shape.h"
#include "bitmap.h"

Shape::Shape()
    : Entity(), red(0), green(0), blue(0), alpha(255)
{
    this->type = "Shape";
    this->name = "General";
}

Shape::Shape(double x, double y, double z)
    : Entity(x, y, z), red(0), green(0), blue(0), alpha(255)
{
    this->type = "Shape";
    this->name = "General";
}

Shape::Shape(Entity *p_perant, double x, double y, double z) : Entity(p_perant, x, y, z), red(0), green(0), blue(0), alpha(255)
{
    this->type = "Shape";
    this->name = "General";
}

Shape::Shape(Shape *e)
    : Entity(e), red(e->red), green(e->green), blue(e->blue), alpha(e->alpha)
{
}

void Shape::applyTransformation()
{
    glColor4ub(red, green, blue, alpha);
    Entity::applyTransformation();
}

void Shape::display()
{
    glPushMatrix();
    applyTransformation();
    glutSolidTeapot(2);
    glPopMatrix();
}

void Shape::setColor(int red, int green, int blue, int alpha)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}

void Shape::displayInfo()
{
    char buffer[1000];                                                                                                                                                                                                                                                                                                                       // Allocate a buffer for the formatted string
    sprintf(buffer, "#%d type: %s | name: %s | x:%.2f y:%.2f z:%.2f | rotation: x:%.2f y:%.2f z:%.2f | scale: x:%.2f y:%.2f z:%.2f | color: R:%.2f G:%.2f B:%.2f Alpha:%.2f ", this->id, this->type.c_str(), this->name.c_str(), translate_x, translate_y, translate_z, rotate_x, rotate_y, rotate_z, scale_x, scale_y, scale_z, red, green, blue, alpha); // Format the string
    renderBitmapText(-0.75, -0.98, buffer, GLUT_BITMAP_HELVETICA_18);
}

Shape *Shape::clone()
{
    return new Shape(this);
}

json Shape::toJSON() {
    return json{{"id", id}, {"type", type}, {"name", name}, {"p_id", p_id}, {"perant", p_perant? p_perant->getName() : "None"},{"translate", {translate_x, translate_y, translate_z}}, {"rotate", {rotate_x, rotate_y, rotate_z}}, {"scale", {scale_x, scale_y, scale_z}}, {"color", {red, green, blue, alpha}}};
}

void Shape::fromJSON(const json &j) {
    Entity::fromJSON(j); // Call base class implementation

    red = j.at("color")[0].get<double>();
    green = j.at("color")[1].get<double>();
    blue = j.at("color")[2].get<double>();
    alpha = j.at("color")[3].get<double>();
}

void Shape::fromJSON(const json &j, int p_id) {
    Entity::fromJSON(j); // Call base class implementation
    this->p_id = p_id;
    red = j.at("color")[0].get<double>();
    green = j.at("color")[1].get<double>();
    blue = j.at("color")[2].get<double>();
    alpha = j.at("color")[3].get<double>();
}



std::string Shape::getDisplayCode() {
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
    temp +="glutSolidTeapot(2);\n";
    temp +="glPopMatrix();\n";
    return temp;
}


