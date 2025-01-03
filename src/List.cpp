#include "List.h"
#include <iostream>
#include "bitmap.h"

List::List(std::string name) : Entity()
{
    type = "List";
    this->name = name;
}

List::List(List *e) : Entity(e)
{
    m_entities = e->m_entities;
}

List::~List()
{
    for (Entity *entity : m_entities)
    {
        delete entity; // Free each allocated Entity
    }
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
    sprintf(buffer, "type: %s | name: %s | x:%.2f y:%.2f z:%.2f | rotation: x:%.2f y:%.2f z:%.2f | scale: x:%.2f y:%.2f z:%.2f ", this->type.c_str(), this->name.c_str(), translate_x, translate_y, translate_z, rotate_x, rotate_y, rotate_z, scale_x, scale_y, scale_z); // Format the string
    renderBitmapText(-0.75, -0.98, buffer, GLUT_BITMAP_HELVETICA_18);
}

void List::pushEntity(Entity* e)
{
    m_entities.push_back(e);
}

// Overload for non-const objects
Entity* List::operator[](int index) {
    for(Entity* i : m_entities) {
        if(i->getId() == index) {
            std::cout << "it returned: " << i << " || " << i->getId() << " || " << i->getName() << std::endl;
            return i;
        }
    }
    return this;
}

bool List::empty() {
    return m_entities.empty();
}

