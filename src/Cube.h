#ifndef CUBE_H
#define CUBE_H
#include "globals.h"
#include "Shape.h"

class Cube : public Shape {
public:
    Cube();
    Cube(double x, double y, double z);
    Cube(Entity *p_perant, double x, double y, double z);
    Cube(Cube *e);
    void display() override;
    std::string getDisplayCode() override;
    Cube* clone() override;
};

#endif
