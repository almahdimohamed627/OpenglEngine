#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include "globals.h"
#include <GL/freeglut.h>

// Base Entity class
class Entity {
protected:
    double translate_x, translate_y, translate_z;
    double rotate_x, rotate_y, rotate_z;
    double scale_x, scale_y, scale_z;
    std::string type; 
    std::string name;
    int id, p_id;
    static int selectedIndex;
    static int count;

public:
    Entity();
    Entity(Entity* e);
    virtual ~Entity();
    static int selected();
    static int selected(int index);
    std::string getType();
    virtual void applyTransformation();
    void transform(char transformation, bool x, bool y, bool z, int amount);
    virtual void display();
    virtual void displayInfo();
};

#endif
