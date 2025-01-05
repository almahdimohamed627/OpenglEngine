#include "List.h"
#include <iostream>
#include "bitmap.h"

List::List(std::string name) : Entity()
{
    type = "List";
    this->name = name;
}

List::List(Entity *p_perant, std::string name) : List(name) {
    this->p_perant = p_perant;
    this->p_id = p_perant->getId();
}

List::List(List *e) : Entity(e)
{
    type = e->type;
    name = e->name;
    m_entities = e->m_entities;
}


void List::display()
{
    glPushMatrix();
    applyTransformation();
    for (Entity *i : m_entities)
    {
        i->display(); // Use -> instead of . for pointers
    }
    glPopMatrix();
}

void List::displayInfo()
{
    char buffer[1000];                                                                                                                                                                                                                                                     // Allocate a buffer for the formatted string
    sprintf(buffer, "#%d type: %s | name: %s | x:%.2f y:%.2f z:%.2f | rotation: x:%.2f y:%.2f z:%.2f | scale: x:%.2f y:%.2f z:%.2f ", this->id, this->type.c_str(), this->name.c_str(), translate_x, translate_y, translate_z, rotate_x, rotate_y, rotate_z, scale_x, scale_y, scale_z); // Format the string
    renderBitmapText(-0.75, -0.98, buffer, GLUT_BITMAP_HELVETICA_18);
}

void List::pushEntity(Entity *e)
{
    m_entities += e;
}


bool List::empty()
{
    return m_entities.empty();
}

List* List::clone() {
    return new List(this);
}