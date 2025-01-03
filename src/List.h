#ifndef LIST_H
#define LIST_H
#include "globals.h"
#include <string>
#include "Entity.h"
#include <GL/freeglut.h>
#include <vector>

class List : public Entity {
protected:

public:
    std::vector<Entity *> m_entities;
    List(std::string name);
    List(List* e);
    ~List();
    void display() override;
    void displayInfo() override;
    void pushEntity(Entity *e);
    // Overload for non-const objects
    Entity* operator[](int index);
    bool empty();
};

#endif
