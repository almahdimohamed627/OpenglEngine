#ifndef SPHERE_H
#define SPHERE_H
#include "globals.h"
#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere();
    Sphere(double x, double y, double z);
    Sphere(Entity *p_perant, double x, double y, double z);
    Sphere(Sphere *e);
    void display() override;
    Sphere* clone() override;
};

#endif
