#ifndef LIST_H
#define LIST_H
#include "globals.h"
#include <string>
#include "Entity.h"
#include <GL/freeglut.h>
#include "MyVector.h"

class List : public Entity {
protected:

public:
    MyVector m_entities;
    List(std::string name);
    List(Entity *p_perant, std::string name);
    List(List* e);
    void display() override;
    void displayInfo() override;
    void pushEntity(Entity *e);
    bool empty();
    List* clone() override;
};

#endif
