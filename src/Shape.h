#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include "globals.h"
#include "Entity.h"
#include <GL/freeglut.h>

// Base Shape class
class Shape : public Entity {
protected:
    double red, green, blue, alpha;

public:
    Shape();
    Shape(int p_id);
    Shape(Shape* e);
    void setColor(int red, int green, int blue, int alpha);
    void applyTransformation() override;
    void display() override;
    void displayInfo() override;
};

#endif
