#ifndef SPHERE_H
#define SPHERE_H
#include "globals.h"
#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere();
    void display() override;
};

#endif
