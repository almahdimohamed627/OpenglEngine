#ifndef ENTITY_H
#define ENTITY_H
#include "globals.h"
#include <GL/glut.h>

// Base Entity class
class Entity {
protected:
    int translate_x, translate_y, translate_z;
    int rotate_x, rotate_y, rotate_z;
    int scale_x, scale_y, scale_z;
    int red, green, blue, alpha;

public:
    Entity();
    virtual ~Entity() = default;

    void transform();
    virtual void display();
};

#endif
