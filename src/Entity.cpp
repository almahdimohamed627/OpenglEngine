#include <typeinfo>
#include <cstdio>
#include <iostream>
#include "Entity.h"
#include "bitmap.h"
#include "globals.h"

int Entity::count = 0; // Definition of static variable
int Entity::selectedIndex = 0;

Entity::Entity()
    : translate_x(0), translate_y(0), translate_z(0),
      rotate_x(0), rotate_y(0), rotate_z(0),
      scale_x(1), scale_y(1), scale_z(1), type("Entity"), name("General"), p_perant(nullptr), p_id(-1)
{
    selectedIndex = count;
    id = count;
    count++;
    //std::cout << "Entity Defualt Constructor: ID = " << id << ", Count = " << count << std::endl;
}

Entity::Entity(double x, double y, double z)
    : translate_x(x), translate_y(y), translate_z(z),
      rotate_x(0), rotate_y(0), rotate_z(0),
      scale_x(1), scale_y(1), scale_z(1), type("Entity"), name("General"), p_perant(nullptr), p_id(-1)
{
    selectedIndex = count;
    id = count;
    count++;
    //std::cout << "Entity xyz Constructor: ID = " << id << ", Count = " << count << std::endl;
}

Entity::Entity(Entity *p_perant, double x, double y, double z)
    : translate_x(x - p_perant->getX()), translate_y(y-p_perant->getY()), translate_z(z-p_perant->getZ()),
      rotate_x(0), rotate_y(0), rotate_z(0),
      scale_x(1), scale_y(1), scale_z(1), type("Entity"), name("General"), p_perant(p_perant), p_id(p_perant->getId())
{
    selectedIndex = count;
    id = count;
    count++;
    //std::cout << "Entity perant Constructor: ID = " << id << ", Count = " << count << std::endl;
}

Entity::Entity(Entity *e)
    : translate_x(e->translate_x), translate_y(e->translate_y), translate_z(e->translate_z),
      rotate_x(e->rotate_x), rotate_y(e->rotate_y), rotate_z(e->rotate_z),
      scale_x(e->scale_x), scale_y(e->scale_y), scale_z(e->scale_z), 
      type(e->type), name(e->name), p_perant(e->p_perant), p_id(e->p_id)
{
    selectedIndex = count;
    id = count;
    count++;
    //std::cout << "Entity Copy Constructor: ID = " << id << ", Count = " << count << std::endl;
}

Entity::~Entity()
{
    count--;
}

void Entity::applyTransformation()
{
    if (selectedIndex == id || selectedIndex == p_id)
    {
        glColor4ub(255, 0, 0, 150);
    }
    glTranslated(translate_x, translate_y, translate_z);
    glRotated(rotate_x, 1, 0, 0);
    glRotated(rotate_y, 0, 1, 0);
    glRotated(rotate_z, 0, 0, 1);
    glScaled(scale_x, scale_y, scale_z);
}

void Entity::display()
{
    glPushMatrix();
    applyTransformation();
    glutSolidTeapot(2);
    glPopMatrix();
}

void Entity::displayInfo()
{
    char buffer[1000];                                                                                                                                                                                                                                                                   // Allocate a buffer for the formatted string
    sprintf(buffer, "#%d type: %s | name: %s | x:%.2f y:%.2f z:%.2f | rotation: x:%.2f y:%.2f z:%.2f | scale: x:%.2f y:%.2f z:%.2f ", this->id, this->type.c_str(), this->name.c_str(), translate_x, translate_y, translate_z, rotate_x, rotate_y, rotate_z, scale_x, scale_y, scale_z); // Format the string
    renderBitmapText(-0.75, -0.98, buffer, GLUT_BITMAP_HELVETICA_18);
}

int Entity::selected()
{
    return selectedIndex;
}
void Entity::selected(int index)
{
    selectedIndex = index;
}

void Entity::transform(char transformation, bool x, bool y, bool z, int amount)
{
    switch (transformation)
    {
    case 't':
        if (x)
        {
            translate_x += amount * 0.1;
        }
        if (y)
        {
            translate_y += amount * 0.1;
        }
        if (z)
        {
            translate_z += amount * 0.1;
        }
        break;
    case 'r':
        if (x)
        {
            rotate_x += amount;
        }
        if (y)
        {
            rotate_y += amount;
        }
        if (z)
        {
            rotate_z += amount;
        }
        break;
    case 's':
        if (x)
        {
            scale_x += amount * 0.1;
        }
        if (y)
        {
            scale_y += amount * 0.1;
        }
        if (z)
        {
            scale_z += amount * 0.1;
        }
        break;

    default:
        break;
    }
}

void Entity::translate(double x, double y, double z)
{
    translate_x = x;
    translate_y = y;
    translate_z = z;
}

std::string Entity::getType()
{
    return type;
}

int Entity::getId()
{
    return id;
}

Entity *Entity::getPerant()
{
    return p_perant;
}

std::string Entity::getName()
{
    return name;
}

double Entity::getX()
{
    return translate_x;
}

double Entity::getY()
{
    return translate_y;
}

double Entity::getZ()
{
    return translate_z;
}

json Entity::toJSON() {
    return json{{"id", id}, {"type", type}, {"name", name}, {"p_id", p_id}, {"perant", p_perant? p_perant->getName() : "None"},{"translate", {translate_x, translate_y, translate_z}}, {"rotate", {rotate_x, rotate_y, rotate_z}}, {"scale", {scale_x, scale_y, scale_z}}};
}

void Entity::fromJSON(const json &j) {
    type = j.at("type").get<std::string>();
    name = j.at("name").get<std::string>();
    translate_x = j.at("translate")[0].get<double>();
    translate_y = j.at("translate")[1].get<double>();
    translate_z = j.at("translate")[2].get<double>();
    rotate_x = j.at("rotate")[0].get<double>();
    rotate_y = j.at("rotate")[1].get<double>();
    rotate_z = j.at("rotate")[2].get<double>();
    scale_x = j.at("scale")[0].get<double>();
    scale_y = j.at("scale")[1].get<double>();
    scale_z = j.at("scale")[2].get<double>();
}

void Entity::fromJSON(const json &j, int p_id) {
    this->p_id = p_id;
    type = j.at("type").get<std::string>();
    name = j.at("name").get<std::string>();
    translate_x = j.at("translate")[0].get<double>();
    translate_y = j.at("translate")[1].get<double>();
    translate_z = j.at("translate")[2].get<double>();
    rotate_x = j.at("rotate")[0].get<double>();
    rotate_y = j.at("rotate")[1].get<double>();
    rotate_z = j.at("rotate")[2].get<double>();
    scale_x = j.at("scale")[0].get<double>();
    scale_y = j.at("scale")[1].get<double>();
    scale_z = j.at("scale")[2].get<double>();
}


std::string Entity::getDisplayCode() {
    char buffer[100];
    std::string temp = "";
    temp +="glPushMatrix();\n";
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

