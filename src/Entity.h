#ifndef ENTITY_H
#define ENTITY_H
#include "globals.h"
#include <GL/freeglut.h>

// Base Entity class
class Entity {
protected:
    double translate_x, translate_y, translate_z;
    double rotate_x, rotate_y, rotate_z;
    double scale_x, scale_y, scale_z;
    double red, green, blue, alpha;
    static int selectedIndex;
    static int count;
    int id;

public:
    Entity();
    Entity(Entity* e);

    virtual ~Entity();
    static int selected();
    static int selected(int index);
    void applyTransformation();
    void transform(char transformation, bool x, bool y, bool z, int amount);
    void setColor(int red, int green, int blue, int alpha);
    virtual void display();
    virtual void displayInfo();
};

#endif
