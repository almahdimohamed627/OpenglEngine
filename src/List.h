#ifndef LIST_H
#define LIST_H
#include "globals.h"
#include <string>
#include "Entity.h"
#include <GL/freeglut.h>
#include <vector>

class List : public Entity {
protected:
    std::vector<Entity *> m_entities;

public:
    List(std::string name);
    List(List* e);
    void display() override;
    void displayInfo() override;
};

#endif
