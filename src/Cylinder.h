#ifndef CYLINDER_H
#define CYLINDER_H
#include "globals.h"
#include "Shape.h"

class Cylinder : public Shape {
public:
    Cylinder();
    Cylinder(double x, double y, double z);
    Cylinder(Entity *p_perant, double x, double y, double z);
    Cylinder(Cylinder *e);
    void display() override;
    std::string getDisplayCode() override;
    Cylinder* clone() override;
};

#endif
