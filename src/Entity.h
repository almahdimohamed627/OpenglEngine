#ifndef ENTITY_H
#define ENTITY_H
#include "globals.h"
#include <GL/freeglut.h>

// Base Entity class
class Entity {
protected:
    int translate_x, translate_y, translate_z;
    int rotate_x, rotate_y, rotate_z;
    int scale_x, scale_y, scale_z;
    int red, green, blue, alpha;
    static int selectedIndex;
    static int count;
    int id;

public:
    Entity();
    virtual ~Entity() = default;
    static int selected();
    static int selected(int index);
    void transform();
    void setColor(int red, int green, int blue, int alpha);
    virtual void display();
};

#endif
